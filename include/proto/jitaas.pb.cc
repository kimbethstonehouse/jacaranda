// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: jitaas.proto

#include "jitaas.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
constexpr FunctionType::FunctionType(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : param_types_()
  , _param_types_cached_byte_size_(0)
  , param_count_(0u)
  , return_count_(0u)
  , return_type_(0u){}
struct FunctionTypeDefaultTypeInternal {
  constexpr FunctionTypeDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~FunctionTypeDefaultTypeInternal() {}
  union {
    FunctionType _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT FunctionTypeDefaultTypeInternal _FunctionType_default_instance_;
constexpr WasmFunction::WasmFunction(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : func_body_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , target_data_layout_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , func_type_(nullptr){}
struct WasmFunctionDefaultTypeInternal {
  constexpr WasmFunctionDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~WasmFunctionDefaultTypeInternal() {}
  union {
    WasmFunction _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT WasmFunctionDefaultTypeInternal _WasmFunction_default_instance_;
constexpr NativeBinary::NativeBinary(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : data_bytes_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , data_length_(0u){}
struct NativeBinaryDefaultTypeInternal {
  constexpr NativeBinaryDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~NativeBinaryDefaultTypeInternal() {}
  union {
    NativeBinary _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT NativeBinaryDefaultTypeInternal _NativeBinary_default_instance_;
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_jitaas_2eproto[3];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_jitaas_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_jitaas_2eproto = nullptr;

const uint32_t TableStruct_jitaas_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::FunctionType, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::FunctionType, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::FunctionType, param_count_),
  PROTOBUF_FIELD_OFFSET(::FunctionType, param_types_),
  PROTOBUF_FIELD_OFFSET(::FunctionType, return_count_),
  PROTOBUF_FIELD_OFFSET(::FunctionType, return_type_),
  ~0u,
  ~0u,
  ~0u,
  0,
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::WasmFunction, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::WasmFunction, func_type_),
  PROTOBUF_FIELD_OFFSET(::WasmFunction, func_body_),
  PROTOBUF_FIELD_OFFSET(::WasmFunction, target_data_layout_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::NativeBinary, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::NativeBinary, data_bytes_),
  PROTOBUF_FIELD_OFFSET(::NativeBinary, data_length_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 10, -1, sizeof(::FunctionType)},
  { 14, -1, -1, sizeof(::WasmFunction)},
  { 23, -1, -1, sizeof(::NativeBinary)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_FunctionType_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_WasmFunction_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_NativeBinary_default_instance_),
};

const char descriptor_table_protodef_jitaas_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\014jitaas.proto\"x\n\014FunctionType\022\023\n\013param_"
  "count\030\001 \001(\r\022\023\n\013param_types\030\002 \003(\r\022\024\n\014retu"
  "rn_count\030\003 \001(\r\022\030\n\013return_type\030\004 \001(\rH\000\210\001\001"
  "B\016\n\014_return_type\"_\n\014WasmFunction\022 \n\tfunc"
  "_type\030\001 \001(\0132\r.FunctionType\022\021\n\tfunc_body\030"
  "\002 \001(\014\022\032\n\022target_data_layout\030\003 \001(\t\"7\n\014Nat"
  "iveBinary\022\022\n\ndata_bytes\030\001 \001(\014\022\023\n\013data_le"
  "ngth\030\002 \001(\r26\n\tJacaranda\022)\n\007compile\022\r.Was"
  "mFunction\032\r.NativeBinary\"\000b\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_jitaas_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_jitaas_2eproto = {
  false, false, 354, descriptor_table_protodef_jitaas_2eproto, "jitaas.proto", 
  &descriptor_table_jitaas_2eproto_once, nullptr, 0, 3,
  schemas, file_default_instances, TableStruct_jitaas_2eproto::offsets,
  file_level_metadata_jitaas_2eproto, file_level_enum_descriptors_jitaas_2eproto, file_level_service_descriptors_jitaas_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_jitaas_2eproto_getter() {
  return &descriptor_table_jitaas_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_jitaas_2eproto(&descriptor_table_jitaas_2eproto);

// ===================================================================

class FunctionType::_Internal {
 public:
  using HasBits = decltype(std::declval<FunctionType>()._has_bits_);
  static void set_has_return_type(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

FunctionType::FunctionType(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned),
  param_types_(arena) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:FunctionType)
}
FunctionType::FunctionType(const FunctionType& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_),
      param_types_(from.param_types_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&param_count_, &from.param_count_,
    static_cast<size_t>(reinterpret_cast<char*>(&return_type_) -
    reinterpret_cast<char*>(&param_count_)) + sizeof(return_type_));
  // @@protoc_insertion_point(copy_constructor:FunctionType)
}

inline void FunctionType::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&param_count_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&return_type_) -
    reinterpret_cast<char*>(&param_count_)) + sizeof(return_type_));
}

FunctionType::~FunctionType() {
  // @@protoc_insertion_point(destructor:FunctionType)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void FunctionType::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void FunctionType::ArenaDtor(void* object) {
  FunctionType* _this = reinterpret_cast< FunctionType* >(object);
  (void)_this;
}
void FunctionType::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void FunctionType::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void FunctionType::Clear() {
// @@protoc_insertion_point(message_clear_start:FunctionType)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  param_types_.Clear();
  ::memset(&param_count_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&return_count_) -
      reinterpret_cast<char*>(&param_count_)) + sizeof(return_count_));
  return_type_ = 0u;
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* FunctionType::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // uint32 param_count = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          param_count_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // repeated uint32 param_types = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedUInt32Parser(_internal_mutable_param_types(), ptr, ctx);
          CHK_(ptr);
        } else if (static_cast<uint8_t>(tag) == 16) {
          _internal_add_param_types(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // uint32 return_count = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 24)) {
          return_count_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // optional uint32 return_type = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 32)) {
          _Internal::set_has_return_type(&has_bits);
          return_type_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  _has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* FunctionType::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:FunctionType)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // uint32 param_count = 1;
  if (this->_internal_param_count() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(1, this->_internal_param_count(), target);
  }

  // repeated uint32 param_types = 2;
  {
    int byte_size = _param_types_cached_byte_size_.load(std::memory_order_relaxed);
    if (byte_size > 0) {
      target = stream->WriteUInt32Packed(
          2, _internal_param_types(), byte_size, target);
    }
  }

  // uint32 return_count = 3;
  if (this->_internal_return_count() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(3, this->_internal_return_count(), target);
  }

  // optional uint32 return_type = 4;
  if (_internal_has_return_type()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(4, this->_internal_return_type(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:FunctionType)
  return target;
}

size_t FunctionType::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:FunctionType)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated uint32 param_types = 2;
  {
    size_t data_size = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      UInt32Size(this->param_types_);
    if (data_size > 0) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
            static_cast<int32_t>(data_size));
    }
    int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(data_size);
    _param_types_cached_byte_size_.store(cached_size,
                                    std::memory_order_relaxed);
    total_size += data_size;
  }

  // uint32 param_count = 1;
  if (this->_internal_param_count() != 0) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32SizePlusOne(this->_internal_param_count());
  }

  // uint32 return_count = 3;
  if (this->_internal_return_count() != 0) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32SizePlusOne(this->_internal_return_count());
  }

  // optional uint32 return_type = 4;
  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32SizePlusOne(this->_internal_return_type());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData FunctionType::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    FunctionType::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*FunctionType::GetClassData() const { return &_class_data_; }

void FunctionType::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<FunctionType *>(to)->MergeFrom(
      static_cast<const FunctionType &>(from));
}


void FunctionType::MergeFrom(const FunctionType& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:FunctionType)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  param_types_.MergeFrom(from.param_types_);
  if (from._internal_param_count() != 0) {
    _internal_set_param_count(from._internal_param_count());
  }
  if (from._internal_return_count() != 0) {
    _internal_set_return_count(from._internal_return_count());
  }
  if (from._internal_has_return_type()) {
    _internal_set_return_type(from._internal_return_type());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void FunctionType::CopyFrom(const FunctionType& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:FunctionType)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool FunctionType::IsInitialized() const {
  return true;
}

void FunctionType::InternalSwap(FunctionType* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  param_types_.InternalSwap(&other->param_types_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(FunctionType, return_type_)
      + sizeof(FunctionType::return_type_)
      - PROTOBUF_FIELD_OFFSET(FunctionType, param_count_)>(
          reinterpret_cast<char*>(&param_count_),
          reinterpret_cast<char*>(&other->param_count_));
}

::PROTOBUF_NAMESPACE_ID::Metadata FunctionType::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_jitaas_2eproto_getter, &descriptor_table_jitaas_2eproto_once,
      file_level_metadata_jitaas_2eproto[0]);
}

// ===================================================================

class WasmFunction::_Internal {
 public:
  static const ::FunctionType& func_type(const WasmFunction* msg);
};

const ::FunctionType&
WasmFunction::_Internal::func_type(const WasmFunction* msg) {
  return *msg->func_type_;
}
WasmFunction::WasmFunction(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:WasmFunction)
}
WasmFunction::WasmFunction(const WasmFunction& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  func_body_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    func_body_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_func_body().empty()) {
    func_body_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_func_body(), 
      GetArenaForAllocation());
  }
  target_data_layout_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    target_data_layout_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_target_data_layout().empty()) {
    target_data_layout_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_target_data_layout(), 
      GetArenaForAllocation());
  }
  if (from._internal_has_func_type()) {
    func_type_ = new ::FunctionType(*from.func_type_);
  } else {
    func_type_ = nullptr;
  }
  // @@protoc_insertion_point(copy_constructor:WasmFunction)
}

inline void WasmFunction::SharedCtor() {
func_body_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  func_body_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
target_data_layout_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  target_data_layout_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
func_type_ = nullptr;
}

WasmFunction::~WasmFunction() {
  // @@protoc_insertion_point(destructor:WasmFunction)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void WasmFunction::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  func_body_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  target_data_layout_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (this != internal_default_instance()) delete func_type_;
}

void WasmFunction::ArenaDtor(void* object) {
  WasmFunction* _this = reinterpret_cast< WasmFunction* >(object);
  (void)_this;
}
void WasmFunction::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void WasmFunction::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void WasmFunction::Clear() {
// @@protoc_insertion_point(message_clear_start:WasmFunction)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  func_body_.ClearToEmpty();
  target_data_layout_.ClearToEmpty();
  if (GetArenaForAllocation() == nullptr && func_type_ != nullptr) {
    delete func_type_;
  }
  func_type_ = nullptr;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* WasmFunction::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // .FunctionType func_type = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          ptr = ctx->ParseMessage(_internal_mutable_func_type(), ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // bytes func_body = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_func_body();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string target_data_layout = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          auto str = _internal_mutable_target_data_layout();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "WasmFunction.target_data_layout"));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* WasmFunction::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:WasmFunction)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // .FunctionType func_type = 1;
  if (this->_internal_has_func_type()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        1, _Internal::func_type(this), target, stream);
  }

  // bytes func_body = 2;
  if (!this->_internal_func_body().empty()) {
    target = stream->WriteBytesMaybeAliased(
        2, this->_internal_func_body(), target);
  }

  // string target_data_layout = 3;
  if (!this->_internal_target_data_layout().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_target_data_layout().data(), static_cast<int>(this->_internal_target_data_layout().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "WasmFunction.target_data_layout");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_target_data_layout(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:WasmFunction)
  return target;
}

size_t WasmFunction::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:WasmFunction)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // bytes func_body = 2;
  if (!this->_internal_func_body().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_func_body());
  }

  // string target_data_layout = 3;
  if (!this->_internal_target_data_layout().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_target_data_layout());
  }

  // .FunctionType func_type = 1;
  if (this->_internal_has_func_type()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *func_type_);
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData WasmFunction::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    WasmFunction::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*WasmFunction::GetClassData() const { return &_class_data_; }

void WasmFunction::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<WasmFunction *>(to)->MergeFrom(
      static_cast<const WasmFunction &>(from));
}


void WasmFunction::MergeFrom(const WasmFunction& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:WasmFunction)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_func_body().empty()) {
    _internal_set_func_body(from._internal_func_body());
  }
  if (!from._internal_target_data_layout().empty()) {
    _internal_set_target_data_layout(from._internal_target_data_layout());
  }
  if (from._internal_has_func_type()) {
    _internal_mutable_func_type()->::FunctionType::MergeFrom(from._internal_func_type());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void WasmFunction::CopyFrom(const WasmFunction& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:WasmFunction)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool WasmFunction::IsInitialized() const {
  return true;
}

void WasmFunction::InternalSwap(WasmFunction* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &func_body_, lhs_arena,
      &other->func_body_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &target_data_layout_, lhs_arena,
      &other->target_data_layout_, rhs_arena
  );
  swap(func_type_, other->func_type_);
}

::PROTOBUF_NAMESPACE_ID::Metadata WasmFunction::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_jitaas_2eproto_getter, &descriptor_table_jitaas_2eproto_once,
      file_level_metadata_jitaas_2eproto[1]);
}

// ===================================================================

class NativeBinary::_Internal {
 public:
};

NativeBinary::NativeBinary(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:NativeBinary)
}
NativeBinary::NativeBinary(const NativeBinary& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  data_bytes_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    data_bytes_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_data_bytes().empty()) {
    data_bytes_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_data_bytes(), 
      GetArenaForAllocation());
  }
  data_length_ = from.data_length_;
  // @@protoc_insertion_point(copy_constructor:NativeBinary)
}

inline void NativeBinary::SharedCtor() {
data_bytes_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  data_bytes_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
data_length_ = 0u;
}

NativeBinary::~NativeBinary() {
  // @@protoc_insertion_point(destructor:NativeBinary)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void NativeBinary::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  data_bytes_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void NativeBinary::ArenaDtor(void* object) {
  NativeBinary* _this = reinterpret_cast< NativeBinary* >(object);
  (void)_this;
}
void NativeBinary::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void NativeBinary::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void NativeBinary::Clear() {
// @@protoc_insertion_point(message_clear_start:NativeBinary)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  data_bytes_.ClearToEmpty();
  data_length_ = 0u;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* NativeBinary::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // bytes data_bytes = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_data_bytes();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // uint32 data_length = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          data_length_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* NativeBinary::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:NativeBinary)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // bytes data_bytes = 1;
  if (!this->_internal_data_bytes().empty()) {
    target = stream->WriteBytesMaybeAliased(
        1, this->_internal_data_bytes(), target);
  }

  // uint32 data_length = 2;
  if (this->_internal_data_length() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(2, this->_internal_data_length(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:NativeBinary)
  return target;
}

size_t NativeBinary::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:NativeBinary)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // bytes data_bytes = 1;
  if (!this->_internal_data_bytes().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_data_bytes());
  }

  // uint32 data_length = 2;
  if (this->_internal_data_length() != 0) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32SizePlusOne(this->_internal_data_length());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData NativeBinary::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    NativeBinary::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*NativeBinary::GetClassData() const { return &_class_data_; }

void NativeBinary::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<NativeBinary *>(to)->MergeFrom(
      static_cast<const NativeBinary &>(from));
}


void NativeBinary::MergeFrom(const NativeBinary& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:NativeBinary)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_data_bytes().empty()) {
    _internal_set_data_bytes(from._internal_data_bytes());
  }
  if (from._internal_data_length() != 0) {
    _internal_set_data_length(from._internal_data_length());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void NativeBinary::CopyFrom(const NativeBinary& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:NativeBinary)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool NativeBinary::IsInitialized() const {
  return true;
}

void NativeBinary::InternalSwap(NativeBinary* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &data_bytes_, lhs_arena,
      &other->data_bytes_, rhs_arena
  );
  swap(data_length_, other->data_length_);
}

::PROTOBUF_NAMESPACE_ID::Metadata NativeBinary::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_jitaas_2eproto_getter, &descriptor_table_jitaas_2eproto_once,
      file_level_metadata_jitaas_2eproto[2]);
}

// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::FunctionType* Arena::CreateMaybeMessage< ::FunctionType >(Arena* arena) {
  return Arena::CreateMessageInternal< ::FunctionType >(arena);
}
template<> PROTOBUF_NOINLINE ::WasmFunction* Arena::CreateMaybeMessage< ::WasmFunction >(Arena* arena) {
  return Arena::CreateMessageInternal< ::WasmFunction >(arena);
}
template<> PROTOBUF_NOINLINE ::NativeBinary* Arena::CreateMaybeMessage< ::NativeBinary >(Arena* arena) {
  return Arena::CreateMessageInternal< ::NativeBinary >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>