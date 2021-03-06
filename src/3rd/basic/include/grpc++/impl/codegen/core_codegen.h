
#ifndef GRPCXX_IMPL_CODEGEN_CORE_CODEGEN_H
#define GRPCXX_IMPL_CODEGEN_CORE_CODEGEN_H

// This file should be compiled as part of grpc++.

#include <grpc++/impl/codegen/core_codegen_interface.h>
#include <grpc/byte_buffer.h>
#include <grpc/impl/codegen/grpc_types.h>

namespace grpc {

/// Implementation of the core codegen interface.
class CoreCodegen : public CoreCodegenInterface {
 private:
  grpc_completion_queue* grpc_completion_queue_create(void* reserved) override;
  void grpc_completion_queue_destroy(grpc_completion_queue* cq) override;
  grpc_event grpc_completion_queue_pluck(grpc_completion_queue* cq, void* tag,
                                         gpr_timespec deadline,
                                         void* reserved) override;

  void* gpr_malloc(size_t size) override;
  void gpr_free(void* p) override;

  void gpr_mu_init(gpr_mu* mu) override;
  void gpr_mu_destroy(gpr_mu* mu) override;
  void gpr_mu_lock(gpr_mu* mu) override;
  void gpr_mu_unlock(gpr_mu* mu) override;
  void gpr_cv_init(gpr_cv* cv) override;
  void gpr_cv_destroy(gpr_cv* cv) override;
  int gpr_cv_wait(gpr_cv* cv, gpr_mu* mu, gpr_timespec abs_deadline) override;
  void gpr_cv_signal(gpr_cv* cv) override;
  void gpr_cv_broadcast(gpr_cv* cv) override;

  void grpc_byte_buffer_destroy(grpc_byte_buffer* bb) override;

  int grpc_byte_buffer_reader_init(grpc_byte_buffer_reader* reader,
                                   grpc_byte_buffer* buffer) override;
  void grpc_byte_buffer_reader_destroy(
      grpc_byte_buffer_reader* reader) override;
  int grpc_byte_buffer_reader_next(grpc_byte_buffer_reader* reader,
                                   grpc_slice* slice) override;

  grpc_byte_buffer* grpc_raw_byte_buffer_create(grpc_slice* slice,
                                                size_t nslices) override;

  grpc_slice grpc_empty_slice() override;
  grpc_slice grpc_slice_malloc(size_t length) override;
  void grpc_slice_unref(grpc_slice slice) override;
  grpc_slice grpc_slice_split_tail(grpc_slice* s, size_t split) override;
  void grpc_slice_buffer_add(grpc_slice_buffer* sb, grpc_slice slice) override;
  void grpc_slice_buffer_pop(grpc_slice_buffer* sb) override;
  grpc_slice grpc_slice_from_static_buffer(const void* buffer,
                                           size_t length) override;
  grpc_slice grpc_slice_from_copied_buffer(const void* buffer,
                                           size_t length) override;
  void grpc_metadata_array_init(grpc_metadata_array* array) override;
  void grpc_metadata_array_destroy(grpc_metadata_array* array) override;

  gpr_timespec gpr_inf_future(gpr_clock_type type) override;
  gpr_timespec gpr_time_0(gpr_clock_type type) override;

  virtual const Status& ok() override;
  virtual const Status& cancelled() override;

  void assert_fail(const char* failed_assertion, const char* file,
                   int line) override;
};

}  // namespace grpc

#endif  // GRPCXX_IMPL_CODEGEN_CORE_CODEGEN_H
