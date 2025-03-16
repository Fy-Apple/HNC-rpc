// Generated by the protocol buffer compiler.  DO NOT EDIT!
// NO CHECKED-IN PROTOBUF GENCODE
// source: hnc_rpc_header.proto
// Protobuf C++ Version: 5.29.3

#ifndef hnc_5frpc_5fheader_2eproto_2epb_2eh
#define hnc_5frpc_5fheader_2eproto_2epb_2eh

#include <limits>
#include <string>
#include <type_traits>
#include <utility>

#include "google/protobuf/runtime_version.h"
#if PROTOBUF_VERSION != 5029003
#error "Protobuf C++ gencode is built with an incompatible version of"
#error "Protobuf C++ headers/runtime. See"
#error "https://protobuf.dev/support/cross-version-runtime-guarantee/#cpp"
#endif
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/generated_message_tctable_decl.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/message.h"
#include "google/protobuf/message_lite.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/unknown_field_set.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_hnc_5frpc_5fheader_2eproto

namespace google {
namespace protobuf {
namespace internal {
template <typename T>
::absl::string_view GetAnyMessageName();
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_hnc_5frpc_5fheader_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_hnc_5frpc_5fheader_2eproto;
namespace hnc_rpc {
class HncRpcHeader;
struct HncRpcHeaderDefaultTypeInternal;
extern HncRpcHeaderDefaultTypeInternal _HncRpcHeader_default_instance_;
}  // namespace hnc_rpc
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

namespace hnc_rpc {

// ===================================================================


// -------------------------------------------------------------------

class HncRpcHeader final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:hnc_rpc.HncRpcHeader) */ {
 public:
  inline HncRpcHeader() : HncRpcHeader(nullptr) {}
  ~HncRpcHeader() PROTOBUF_FINAL;

#if defined(PROTOBUF_CUSTOM_VTABLE)
  void operator delete(HncRpcHeader* msg, std::destroying_delete_t) {
    SharedDtor(*msg);
    ::google::protobuf::internal::SizedDelete(msg, sizeof(HncRpcHeader));
  }
#endif

  template <typename = void>
  explicit PROTOBUF_CONSTEXPR HncRpcHeader(
      ::google::protobuf::internal::ConstantInitialized);

  inline HncRpcHeader(const HncRpcHeader& from) : HncRpcHeader(nullptr, from) {}
  inline HncRpcHeader(HncRpcHeader&& from) noexcept
      : HncRpcHeader(nullptr, std::move(from)) {}
  inline HncRpcHeader& operator=(const HncRpcHeader& from) {
    CopyFrom(from);
    return *this;
  }
  inline HncRpcHeader& operator=(HncRpcHeader&& from) noexcept {
    if (this == &from) return *this;
    if (::google::protobuf::internal::CanMoveWithInternalSwap(GetArena(), from.GetArena())) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const HncRpcHeader& default_instance() {
    return *internal_default_instance();
  }
  static inline const HncRpcHeader* internal_default_instance() {
    return reinterpret_cast<const HncRpcHeader*>(
        &_HncRpcHeader_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 0;
  friend void swap(HncRpcHeader& a, HncRpcHeader& b) { a.Swap(&b); }
  inline void Swap(HncRpcHeader* other) {
    if (other == this) return;
    if (::google::protobuf::internal::CanUseInternalSwap(GetArena(), other->GetArena())) {
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(HncRpcHeader* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  HncRpcHeader* New(::google::protobuf::Arena* arena = nullptr) const {
    return ::google::protobuf::Message::DefaultConstruct<HncRpcHeader>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const HncRpcHeader& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const HncRpcHeader& from) { HncRpcHeader::MergeImpl(*this, from); }

  private:
  static void MergeImpl(
      ::google::protobuf::MessageLite& to_msg,
      const ::google::protobuf::MessageLite& from_msg);

  public:
  bool IsInitialized() const {
    return true;
  }
  ABSL_ATTRIBUTE_REINITIALIZES void Clear() PROTOBUF_FINAL;
  #if defined(PROTOBUF_CUSTOM_VTABLE)
  private:
  static ::size_t ByteSizeLong(const ::google::protobuf::MessageLite& msg);
  static ::uint8_t* _InternalSerialize(
      const MessageLite& msg, ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream);

  public:
  ::size_t ByteSizeLong() const { return ByteSizeLong(*this); }
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const {
    return _InternalSerialize(*this, target, stream);
  }
  #else   // PROTOBUF_CUSTOM_VTABLE
  ::size_t ByteSizeLong() const final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  #endif  // PROTOBUF_CUSTOM_VTABLE
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  static void SharedDtor(MessageLite& self);
  void InternalSwap(HncRpcHeader* other);
 private:
  template <typename T>
  friend ::absl::string_view(
      ::google::protobuf::internal::GetAnyMessageName)();
  static ::absl::string_view FullMessageName() { return "hnc_rpc.HncRpcHeader"; }

 protected:
  explicit HncRpcHeader(::google::protobuf::Arena* arena);
  HncRpcHeader(::google::protobuf::Arena* arena, const HncRpcHeader& from);
  HncRpcHeader(::google::protobuf::Arena* arena, HncRpcHeader&& from) noexcept
      : HncRpcHeader(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::internal::ClassData* GetClassData() const PROTOBUF_FINAL;
  static void* PlacementNew_(const void*, void* mem,
                             ::google::protobuf::Arena* arena);
  static constexpr auto InternalNewImpl_();
  static const ::google::protobuf::internal::ClassDataFull _class_data_;

 public:
  ::google::protobuf::Metadata GetMetadata() const;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kServerNameFieldNumber = 1,
    kMethodNameFieldNumber = 2,
    kArgsSizeFieldNumber = 3,
  };
  // bytes server_name = 1;
  void clear_server_name() ;
  const std::string& server_name() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_server_name(Arg_&& arg, Args_... args);
  std::string* mutable_server_name();
  PROTOBUF_NODISCARD std::string* release_server_name();
  void set_allocated_server_name(std::string* value);

  private:
  const std::string& _internal_server_name() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_server_name(
      const std::string& value);
  std::string* _internal_mutable_server_name();

  public:
  // bytes method_name = 2;
  void clear_method_name() ;
  const std::string& method_name() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_method_name(Arg_&& arg, Args_... args);
  std::string* mutable_method_name();
  PROTOBUF_NODISCARD std::string* release_method_name();
  void set_allocated_method_name(std::string* value);

  private:
  const std::string& _internal_method_name() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_method_name(
      const std::string& value);
  std::string* _internal_mutable_method_name();

  public:
  // uint32 args_size = 3;
  void clear_args_size() ;
  ::uint32_t args_size() const;
  void set_args_size(::uint32_t value);

  private:
  ::uint32_t _internal_args_size() const;
  void _internal_set_args_size(::uint32_t value);

  public:
  // @@protoc_insertion_point(class_scope:hnc_rpc.HncRpcHeader)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      2, 3, 0,
      0, 2>
      _table_;

  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {
    inline explicit constexpr Impl_(
        ::google::protobuf::internal::ConstantInitialized) noexcept;
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena);
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena, const Impl_& from,
                          const HncRpcHeader& from_msg);
    ::google::protobuf::internal::ArenaStringPtr server_name_;
    ::google::protobuf::internal::ArenaStringPtr method_name_;
    ::uint32_t args_size_;
    ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_hnc_5frpc_5fheader_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// HncRpcHeader

// bytes server_name = 1;
inline void HncRpcHeader::clear_server_name() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.server_name_.ClearToEmpty();
}
inline const std::string& HncRpcHeader::server_name() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:hnc_rpc.HncRpcHeader.server_name)
  return _internal_server_name();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void HncRpcHeader::set_server_name(Arg_&& arg,
                                                     Args_... args) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.server_name_.SetBytes(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:hnc_rpc.HncRpcHeader.server_name)
}
inline std::string* HncRpcHeader::mutable_server_name() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_server_name();
  // @@protoc_insertion_point(field_mutable:hnc_rpc.HncRpcHeader.server_name)
  return _s;
}
inline const std::string& HncRpcHeader::_internal_server_name() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.server_name_.Get();
}
inline void HncRpcHeader::_internal_set_server_name(const std::string& value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.server_name_.Set(value, GetArena());
}
inline std::string* HncRpcHeader::_internal_mutable_server_name() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  return _impl_.server_name_.Mutable( GetArena());
}
inline std::string* HncRpcHeader::release_server_name() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  // @@protoc_insertion_point(field_release:hnc_rpc.HncRpcHeader.server_name)
  return _impl_.server_name_.Release();
}
inline void HncRpcHeader::set_allocated_server_name(std::string* value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.server_name_.SetAllocated(value, GetArena());
  if (::google::protobuf::internal::DebugHardenForceCopyDefaultString() && _impl_.server_name_.IsDefault()) {
    _impl_.server_name_.Set("", GetArena());
  }
  // @@protoc_insertion_point(field_set_allocated:hnc_rpc.HncRpcHeader.server_name)
}

// bytes method_name = 2;
inline void HncRpcHeader::clear_method_name() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.method_name_.ClearToEmpty();
}
inline const std::string& HncRpcHeader::method_name() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:hnc_rpc.HncRpcHeader.method_name)
  return _internal_method_name();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void HncRpcHeader::set_method_name(Arg_&& arg,
                                                     Args_... args) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.method_name_.SetBytes(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:hnc_rpc.HncRpcHeader.method_name)
}
inline std::string* HncRpcHeader::mutable_method_name() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_method_name();
  // @@protoc_insertion_point(field_mutable:hnc_rpc.HncRpcHeader.method_name)
  return _s;
}
inline const std::string& HncRpcHeader::_internal_method_name() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.method_name_.Get();
}
inline void HncRpcHeader::_internal_set_method_name(const std::string& value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.method_name_.Set(value, GetArena());
}
inline std::string* HncRpcHeader::_internal_mutable_method_name() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  return _impl_.method_name_.Mutable( GetArena());
}
inline std::string* HncRpcHeader::release_method_name() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  // @@protoc_insertion_point(field_release:hnc_rpc.HncRpcHeader.method_name)
  return _impl_.method_name_.Release();
}
inline void HncRpcHeader::set_allocated_method_name(std::string* value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.method_name_.SetAllocated(value, GetArena());
  if (::google::protobuf::internal::DebugHardenForceCopyDefaultString() && _impl_.method_name_.IsDefault()) {
    _impl_.method_name_.Set("", GetArena());
  }
  // @@protoc_insertion_point(field_set_allocated:hnc_rpc.HncRpcHeader.method_name)
}

// uint32 args_size = 3;
inline void HncRpcHeader::clear_args_size() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.args_size_ = 0u;
}
inline ::uint32_t HncRpcHeader::args_size() const {
  // @@protoc_insertion_point(field_get:hnc_rpc.HncRpcHeader.args_size)
  return _internal_args_size();
}
inline void HncRpcHeader::set_args_size(::uint32_t value) {
  _internal_set_args_size(value);
  // @@protoc_insertion_point(field_set:hnc_rpc.HncRpcHeader.args_size)
}
inline ::uint32_t HncRpcHeader::_internal_args_size() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.args_size_;
}
inline void HncRpcHeader::_internal_set_args_size(::uint32_t value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.args_size_ = value;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace hnc_rpc


// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // hnc_5frpc_5fheader_2eproto_2epb_2eh
