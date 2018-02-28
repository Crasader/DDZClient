// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: base.proto

#ifndef PROTOBUF_base_2eproto__INCLUDED
#define PROTOBUF_base_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3003000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3003000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
namespace base {
class ErrorCode;
class ErrorCodeDefaultTypeInternal;
extern ErrorCodeDefaultTypeInternal _ErrorCode_default_instance_;
}  // namespace base

namespace base {

namespace protobuf_base_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[];
  static const ::google::protobuf::uint32 offsets[];
  static void InitDefaultsImpl();
  static void Shutdown();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_base_2eproto

enum ERROR_CODE {
  SUCCESS = 0,
  ACCOUNT_NOT_EXIST = 1,
  ACCOUNT_OR_PASSWD_ERROR = 2,
  ALREADY_LOGON = 3,
  ILLEGAL_PARAM = 4,
  ACCOUNT_HAS_EXIST = 5,
  ACCOUNT_INVALIDATE = 6,
  ROOM_NOT_EXIST = 7,
  ROOM_PLAYER_FULL = 8,
  ROOM_ENTER_FAIL = 9,
  CREATE_ROOM_ERROR = 10,
  PLAYER_NOT_IN_ROOM = 11,
  PLAYER_HAS_IN_ROOM = 12,
  ERROR_HAS_READY = 13,
  ERROR_USER_NOT_READY = 14,
  ROOM_HAS_START = 15,
  NOT_TURN_YOU = 16,
  COMB_FAIL = 17,
  MUST_PLAY = 18,
  CHOOSE_ERROR = 19,
  USER_NOT_FOUND = 20,
  ROOM_STATE_IS_NOT_PLAYING = 21,
  NOT_FOUND_CARD = 22
};
bool ERROR_CODE_IsValid(int value);
const ERROR_CODE ERROR_CODE_MIN = SUCCESS;
const ERROR_CODE ERROR_CODE_MAX = NOT_FOUND_CARD;
const int ERROR_CODE_ARRAYSIZE = ERROR_CODE_MAX + 1;

const ::google::protobuf::EnumDescriptor* ERROR_CODE_descriptor();
inline const ::std::string& ERROR_CODE_Name(ERROR_CODE value) {
  return ::google::protobuf::internal::NameOfEnum(
    ERROR_CODE_descriptor(), value);
}
inline bool ERROR_CODE_Parse(
    const ::std::string& name, ERROR_CODE* value) {
  return ::google::protobuf::internal::ParseNamedEnum<ERROR_CODE>(
    ERROR_CODE_descriptor(), name, value);
}
// ===================================================================

class ErrorCode : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:base.ErrorCode) */ {
 public:
  ErrorCode();
  virtual ~ErrorCode();

  ErrorCode(const ErrorCode& from);

  inline ErrorCode& operator=(const ErrorCode& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ErrorCode& default_instance();

  static inline const ErrorCode* internal_default_instance() {
    return reinterpret_cast<const ErrorCode*>(
               &_ErrorCode_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(ErrorCode* other);

  // implements Message ----------------------------------------------

  inline ErrorCode* New() const PROTOBUF_FINAL { return New(NULL); }

  ErrorCode* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const ErrorCode& from);
  void MergeFrom(const ErrorCode& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(ErrorCode* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional bytes desc = 2;
  bool has_desc() const;
  void clear_desc();
  static const int kDescFieldNumber = 2;
  const ::std::string& desc() const;
  void set_desc(const ::std::string& value);
  #if LANG_CXX11
  void set_desc(::std::string&& value);
  #endif
  void set_desc(const char* value);
  void set_desc(const void* value, size_t size);
  ::std::string* mutable_desc();
  ::std::string* release_desc();
  void set_allocated_desc(::std::string* desc);

  // required .base.ERROR_CODE code = 1;
  bool has_code() const;
  void clear_code();
  static const int kCodeFieldNumber = 1;
  ::base::ERROR_CODE code() const;
  void set_code(::base::ERROR_CODE value);

  // @@protoc_insertion_point(class_scope:base.ErrorCode)
 private:
  void set_has_code();
  void clear_has_code();
  void set_has_desc();
  void clear_has_desc();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr desc_;
  int code_;
  friend struct protobuf_base_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// ErrorCode

// required .base.ERROR_CODE code = 1;
inline bool ErrorCode::has_code() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ErrorCode::set_has_code() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ErrorCode::clear_has_code() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ErrorCode::clear_code() {
  code_ = 0;
  clear_has_code();
}
inline ::base::ERROR_CODE ErrorCode::code() const {
  // @@protoc_insertion_point(field_get:base.ErrorCode.code)
  return static_cast< ::base::ERROR_CODE >(code_);
}
inline void ErrorCode::set_code(::base::ERROR_CODE value) {
  assert(::base::ERROR_CODE_IsValid(value));
  set_has_code();
  code_ = value;
  // @@protoc_insertion_point(field_set:base.ErrorCode.code)
}

// optional bytes desc = 2;
inline bool ErrorCode::has_desc() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ErrorCode::set_has_desc() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ErrorCode::clear_has_desc() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ErrorCode::clear_desc() {
  desc_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_desc();
}
inline const ::std::string& ErrorCode::desc() const {
  // @@protoc_insertion_point(field_get:base.ErrorCode.desc)
  return desc_.GetNoArena();
}
inline void ErrorCode::set_desc(const ::std::string& value) {
  set_has_desc();
  desc_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:base.ErrorCode.desc)
}
#if LANG_CXX11
inline void ErrorCode::set_desc(::std::string&& value) {
  set_has_desc();
  desc_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:base.ErrorCode.desc)
}
#endif
inline void ErrorCode::set_desc(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_desc();
  desc_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:base.ErrorCode.desc)
}
inline void ErrorCode::set_desc(const void* value, size_t size) {
  set_has_desc();
  desc_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:base.ErrorCode.desc)
}
inline ::std::string* ErrorCode::mutable_desc() {
  set_has_desc();
  // @@protoc_insertion_point(field_mutable:base.ErrorCode.desc)
  return desc_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* ErrorCode::release_desc() {
  // @@protoc_insertion_point(field_release:base.ErrorCode.desc)
  clear_has_desc();
  return desc_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ErrorCode::set_allocated_desc(::std::string* desc) {
  if (desc != NULL) {
    set_has_desc();
  } else {
    clear_has_desc();
  }
  desc_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), desc);
  // @@protoc_insertion_point(field_set_allocated:base.ErrorCode.desc)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)


}  // namespace base

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::base::ERROR_CODE> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::base::ERROR_CODE>() {
  return ::base::ERROR_CODE_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_base_2eproto__INCLUDED
