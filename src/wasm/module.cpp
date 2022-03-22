#include <cstring>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <module.h>
#include <payload.h>
#include <section.h>
#include <jitaas.h>

Module::Module(const std::string &filename) {
    // Open the file for reading
    int fd = open(filename.c_str(), O_RDONLY);
    if (fd < 0) {
        throw load_exception("local: unable to open file '" + filename + "'");
    }

    // Stat the file, so we can obtain its size
    struct stat64 st;
    if (fstat64(fd, &st) < 0) {
        close(fd);
        throw load_exception("local: unable to stat file '" + filename + "'");
    }

    // Check that we can at least read the magic number and version number (the first eight bytes)
    buffer_size_ = (size_t)st.st_size;

    if (buffer_size_ < 8) {
        close(fd);
        throw load_exception("local: invalid file size for '" + filename + "'");
    }

    // Now, map the file into memory, and close the descriptor.  Once mapped, it's OK to close the FD.
    buffer_ = (const char *)mmap(nullptr, buffer_size_, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);

    // Check to see if the mapping failed.
    if (buffer_ == MAP_FAILED) {
        throw load_exception("local: unable to map file '" + filename + "'");
    }

    // Store the buffer end pointer, which is the byte AFTER the last byte of the mapped file.
    buffer_end_ = (const char *)((uintptr_t)buffer_ + buffer_size_);

    parse_sections();
}

void Module::parse_sections() {
    // Check magic
    const char *magic = &buffer_[0];
    if (memcmp(magic, wasm_magic_reference, sizeof(wasm_magic_reference)) != 0) {
        throw load_exception("local: invalid magic number");
    }

    // Check version
    const char *version = &buffer_[4];
    if (memcmp(version, wasm_version_reference, sizeof(wasm_version_reference)) != 0) {
        throw load_exception("local: invalid version number");
    }

    //Populate the section mapping
    const char *offset = &buffer_[8];
    while (offset < buffer_end_) {
        // Read the section id
        char section_id = *offset++;

        // Read the section length
        unsigned int section_length = read_uleb128(offset);

        Payload payload(offset, section_length);

        // Create the section objects of the appropriate type, and put them into the map.  There should be at most ONE
        // well-defined section, but there can be multiple custom sections.  The specification says that the
        // well-defined sections need to appear in a specific order, but we don't care about that here.
        switch (section_id) {
            case 0:
                custom_sections_.push_back(new CustomSection(payload));
                break;
            case 1:
                add_section(new TypeSection(payload));
                break;
            case 2:
                add_section(new ImportSection(payload));
                break;
            case 3:
                add_section(new FunctionSection(payload));
                break;
            case 4:
                add_section(new TableSection(payload));
                break;
            case 5:
                add_section(new MemorySection(payload));
                break;
            case 6:
                add_section(new GlobalSection(payload));
                break;
            case 7:
                add_section(new ExportSection(payload));
                break;
            case 8:
                add_section(new StartSection(payload));
                break;
            case 9:
                add_section(new ElementSection(payload));
                break;
            case 10:
                add_section(new CodeSection(payload));
                break;
            case 11:
                add_section(new DataSection(payload));
                break;
            case 12:
                add_section(new DataCountSection(payload));
                break;

            default:
                throw load_exception("local: unknown section id");
        }

        // Increment the current file pointer by the stated section length.
        offset += section_length;
    }
}