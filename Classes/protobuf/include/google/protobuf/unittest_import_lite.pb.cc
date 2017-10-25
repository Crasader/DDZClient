// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/unittest_import_lite.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include <google/protobuf/unittest_import_lite.pb.h>

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
// @@protoc_insertion_point(includes)

namespace protobuf_unittest_import {
class ImportMessageLiteDefaultTypeInternal : public ::google::protobuf::internal::ExplicitlyConstructed<ImportMessageLite> {
} _ImportMessageLite_default_instance_;

namespace protobuf_google_2fprotobuf_2funittest_5fimport_5flite_2eproto {

PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::ParseTableField
    const TableStruct::entries[] = {
  {0, 0, 0, ::google::protobuf::internal::kInvalidMask, 0, 0},
};

PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::AuxillaryParseTableField
    const TableStruct::aux[] = {
  ::google::protobuf::internal::AuxillaryParseTableField(),
};
PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::ParseTable const
    TableStruct::schema[] = {
  { NULL, NULL, 0, -1, -1, false },
};


void TableStruct::Shutdown() {
  _ImportMessageLite_default_instance_.Shutdown();
}

void TableStruct::InitDefaultsImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::InitProtobufDefaults();
  ::protobuf_unittest_import::protobuf_google_2fprotobuf_2funittest_5fimport_5fpublic_5flite_2eproto::InitDefaults();
  _ImportMessageLite_default_instance_.DefaultConstruct();
}

void InitDefaults() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &TableStruct::InitDefaultsImpl);
}
void AddDescriptorsImpl() {
  InitDefaults();
  ::protobuf_unittest_import::protobuf_google_2fprotobuf_2funittest_5fimport_5fpublic_5flite_2eproto::AddDescriptors();
  ::google::protobuf::internal::OnShutdown(&TableStruct::Shutdown);
}

void AddDescriptors() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &AddDescriptorsImpl);
}
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;
#endif  // GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER

}  // namespace protobuf_google_2fprotobuf_2funittest_5fimport_5flite_2eproto

bool ImportEnumLite_IsValid(int value) {
  switch (value) {
    case 7:
    case 8:
    case 9:
      return true;
    default:
      return false;
  }
}


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int ImportMessageLite::kDFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

ImportMessageLite::ImportMessageLite()
  : ::google::protobuf::MessageLite(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_google_2fprotobuf_2funittest_5fimport_5flite_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:protobuf_unittest_import.ImportMessageLite)
}
ImportMessageLite::ImportMessageLite(const ImportMessageLite& from)
  : ::google::protobuf::MessageLite(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  d_ = from.d_;
  // @@protoc_insertion_point(copy_constructor:protobuf_unittest_import.ImportMessageLite)
}

void ImportMessageLite::SharedCtor() {
  _cached_size_ = 0;
  d_ = 0;
}

ImportMessageLite::~ImportMessageLite() {
  // @@protoc_insertion_point(destructor:protobuf_unittest_import.ImportMessageLite)
  SharedDtor();
}

void ImportMessageLite::SharedDtor() {
}

void ImportMessageLite::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ImportMessageLite& ImportMessageLite::default_instance() {
  protobuf_google_2fprotobuf_2funittest_5fimport_5flite_2eproto::InitDefaults();
  return *internal_default_instance();
}

ImportMessageLite* ImportMessageLite::New(::google::protobuf::Arena* arena) const {
  ImportMessageLite* n = new ImportMessageLite;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void ImportMessageLite::Clear() {
// @@protoc_insertion_point(message_clear_start:protobuf_unittest_import.ImportMessageLite)
  d_ = 0;
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool ImportMessageLite::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  ::google::protobuf::io::LazyStringOutputStream unknown_fields_string(
      ::google::protobuf::NewPermanentCallback(&_internal_metadata_,
          &::google::protobuf::internal::InternalMetadataWithArenaLite::
              mutable_unknown_fields));
  ::google::protobuf::io::CodedOutputStream unknown_fields_stream(
      &unknown_fields_string, false);
  // @@protoc_insertion_point(parse_start:protobuf_unittest_import.ImportMessageLite)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 d = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u)) {
          set_has_d();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &d_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(
            input, tag, &unknown_fields_stream));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:protobuf_unittest_import.ImportMessageLite)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:protobuf_unittest_import.ImportMessageLite)
  return false;
#undef DO_
}

void ImportMessageLite::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:protobuf_unittest_import.ImportMessageLite)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional int32 d = 1;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->d(), output);
  }

  output->WriteRaw(unknown_fields().data(),
                   static_cast<int>(unknown_fields().size()));
  // @@protoc_insertion_point(serialize_end:protobuf_unittest_import.ImportMessageLite)
}

size_t ImportMessageLite::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:protobuf_unittest_import.ImportMessageLite)
  size_t total_size = 0;

  total_size += unknown_fields().size();

  // optional int32 d = 1;
  if (has_d()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->d());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ImportMessageLite::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const ImportMessageLite*>(&from));
}

void ImportMessageLite::MergeFrom(const ImportMessageLite& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:protobuf_unittest_import.ImportMessageLite)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.has_d()) {
    set_d(from.d());
  }
}

void ImportMessageLite::CopyFrom(const ImportMessageLite& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:protobuf_unittest_import.ImportMessageLite)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ImportMessageLite::IsInitialized() const {
  return true;
}

void ImportMessageLite::Swap(ImportMessageLite* other) {
  if (other == this) return;
  InternalSwap(other);
}
void ImportMessageLite::InternalSwap(ImportMessageLite* other) {
  std::swap(d_, other->d_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::std::string ImportMessageLite::GetTypeName() const {
  return "protobuf_unittest_import.ImportMessageLite";
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// ImportMessageLite

// optional int32 d = 1;
bool ImportMessageLite::has_d() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void ImportMessageLite::set_has_d() {
  _has_bits_[0] |= 0x00000001u;
}
void ImportMessageLite::clear_has_d() {
  _has_bits_[0] &= ~0x00000001u;
}
void ImportMessageLite::clear_d() {
  d_ = 0;
  clear_has_d();
}
::google::protobuf::int32 ImportMessageLite::d() const {
  // @@protoc_insertion_point(field_get:protobuf_unittest_import.ImportMessageLite.d)
  return d_;
}
void ImportMessageLite::set_d(::google::protobuf::int32 value) {
  set_has_d();
  d_ = value;
  // @@protoc_insertion_point(field_set:protobuf_unittest_import.ImportMessageLite.d)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace protobuf_unittest_import

// @@protoc_insertion_point(global_scope)
