#include <cstring>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <static-module.h>
#include <payload.h>
#include <section.h>
#include <fstream>

StaticModule::StaticModule(const std::string &filename) {
    // Open the file for reading
    int fd = open(filename.c_str(), O_RDONLY);
    if (fd < 0) {
        throw parse_exception("unable to open file '" + filename + "'");
    }

    // Stat the file to obtain the size
    struct stat64 st;
    if (fstat64(fd, &st) < 0) {
        close(fd);
        throw parse_exception("unable to stat file '" + filename + "'");
    }

    // Check that we can at least read the magic number and version number (the first eight bytes)
    buffer_size_ = (size_t)st.st_size;

    if (buffer_size_ < 8) {
        close(fd);
        throw parse_exception("invalid file size for '" + filename + "'");
    }

    // Now, map the file into memory, and close the file descriptor
    buffer_ = (const char *)mmap(nullptr, buffer_size_, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);

    // Check to see if the mapping failed
    if (buffer_ == MAP_FAILED) {
        throw parse_exception("unable to map file '" + filename + "'");
    }

    // Store the buffer end pointer, which is the byte AFTER the last byte of the mapped file
    buffer_end_ = (const char *)((uintptr_t)buffer_ + buffer_size_);

    // Decode the module...
    parse_sections();
}

StaticModule::~StaticModule() { munmap((void *)buffer_, buffer_size_); }

void StaticModule::parse_sections() {
    // Check magic number
    const char *magic = &buffer_[0];
    if (memcmp(magic, wasm_magic_reference, sizeof(wasm_magic_reference)) != 0) {
        throw parse_exception("invalid magic number");
    }

    // Check version number
    const char *version = &buffer_[4];
    if (memcmp(version, wasm_version_reference, sizeof(wasm_version_reference)) != 0) {
        throw parse_exception("invalid version number");
    }

    // Populate the section mapping
    const char *offset = &buffer_[8];
    while (offset < buffer_end_) {
        // Read the section id
        char section_id = read_uleb128(offset, VARUINT7);

        // Read the section length
        unsigned int section_length = read_uleb128(offset, VARUINT32);

        // Create the section objects of the appropriate type, and put them into the map.
        // There should be at most ONE of each well-defined section, but there can be multiple
        // custom sections. The specification says that the well-defined sections need to
        // appear in a specific order, but we don't care about that here.
        Payload payload(offset, section_length);
        switch (section_id) {
            case 0:
                custom_sections_.push_back(new Wasm::CustomSection(payload));
                break;
            case 1:
                add_section(new Wasm::TypeSection(payload));
                break;
            case 2:
                add_section(new Wasm::ImportSection(payload));
                break;
            case 3:
                add_section(new Wasm::FunctionSection(payload));
                break;
            case 4:
                add_section(new Wasm::TableSection(payload));
                break;
            case 5:
                add_section(new Wasm::MemorySection(payload));
                break;
            case 6:
                add_section(new Wasm::GlobalSection(payload));
                break;
            case 7:
                add_section(new Wasm::ExportSection(payload));
                break;
            case 8:
                add_section(new Wasm::StartSection(payload));
                break;
            case 9:
                add_section(new Wasm::ElementSection(payload));
                break;
            case 10:
                add_section(new Wasm::CodeSection(payload));
                break;
            case 11:
                add_section(new Wasm::DataSection(payload));
                break;

            default:
                throw parse_exception("unknown section id");
        }

        // Increment the current file pointer by the stated section length.
        offset += section_length;
    }
}