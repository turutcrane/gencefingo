
#ifndef CEFINGO_H_
#define CEFINGO_H_
#include "include/capi/cef_app_capi.h"
#include "include/capi/cef_client_capi.h"
#include "include/capi/cef_v8_capi.h"
#include "include/cef_version.h"
#include "cefingo_base.h"
#include "cefingo_values.h"

CEFINGO_REF_COUNTER_WRAPPER(cef_app_t, cefingo_app_wrapper_t);
CEFINGO_REF_COUNTER_WRAPPER(cef_client_t, cefingo_client_wrapper_t);
CEFINGO_REF_COUNTER_WRAPPER(cef_browser_process_handler_t, cefingo_browser_process_handler_wrapper_t);
CEFINGO_REF_COUNTER_WRAPPER(cef_life_span_handler_t, cefingo_life_span_handler_wrapper_t);
CEFINGO_REF_COUNTER_WRAPPER(cef_render_process_handler_t, cefingo_render_process_handler_wrapper_t);
CEFINGO_REF_COUNTER_WRAPPER(cef_v8array_buffer_release_callback_t, cefingo_v8array_buffer_release_callback_wrapper_t);
CEFINGO_REF_COUNTER_WRAPPER(cef_v8handler_t, cefingo_v8handler_wrapper_t);
CEFINGO_REF_COUNTER_WRAPPER(cef_load_handler_t, cefingo_load_handler_wrapper_t);
CEFINGO_REF_COUNTER_WRAPPER(cef_scheme_handler_factory_t, cefingo_scheme_handler_factory_wrapper_t);
CEFINGO_REF_COUNTER_WRAPPER(cef_resource_handler_t, cefingo_resource_handler_wrapper_t);
CEFINGO_REF_COUNTER_WRAPPER(cef_run_file_dialog_callback_t, cefingo_run_file_dialog_callback_wrapper_t);

extern void cefingo_construct_life_span_handler(cefingo_life_span_handler_wrapper_t *handler);
extern void cefingo_construct_browser_process_handler(cefingo_browser_process_handler_wrapper_t *handler);
extern void cefingo_construct_client(cefingo_client_wrapper_t* client);
extern void cefingo_construct_app(cefingo_app_wrapper_t* app);
extern void cefingo_construct_render_process_handler(cefingo_render_process_handler_wrapper_t* handler);
extern void cefingo_construct_load_handler(cefingo_load_handler_wrapper_t* handler);
extern void cefingo_construct_scheme_handler_factory(cefingo_scheme_handler_factory_wrapper_t *factory);
extern void cefingo_construct_resource_handler(cefingo_resource_handler_wrapper_t *handler);
extern void cefingo_construct_run_file_dialog_callback(cefingo_run_file_dialog_callback_wrapper_t *callback);

extern cef_v8context_t *cefingo_frame_get_v8context(cef_frame_t *self);
extern cef_string_userfree_t cefingo_frame_get_url(cef_frame_t* self);

extern int cefingo_scheme_registrar_add_custom_scheme(struct _cef_scheme_registrar_t* self,
        const cef_string_t* scheme_name, int is_standard, int is_local,
        int is_display_isolated, int is_secure, int is_cors_enabled, int is_csp_bypassing);

extern void cefingo_callback_cont(struct _cef_callback_t* self);
extern void cefingo_callback_cancel(struct _cef_callback_t* self);

extern cef_string_userfree_t cefingo_request_get_url(struct _cef_request_t* self);

extern void cefingo_response_set_error(struct _cef_response_t* self, cef_errorcode_t error);
extern void cefingo_response_set_status(struct _cef_response_t* self, int status);
extern void cefingo_response_set_status_text(struct _cef_response_t* self, const cef_string_t* statusText);
extern void cefingo_response_set_mime_type(struct _cef_response_t* self, const cef_string_t* mimeType);
extern void cefingo_response_get_header_map(struct _cef_response_t* self, cef_string_multimap_t map);
extern void cefingo_response_set_header_map(struct _cef_response_t* self, cef_string_multimap_t headerMap);

extern int cefingo_process_message_is_valid(struct _cef_process_message_t* self);
extern int cefingo_process_message_is_read_only(struct _cef_process_message_t* self);
extern struct _cef_process_message_t* cefingo_process_message_copy(
    struct _cef_process_message_t* self);
extern cef_string_userfree_t cefingo_process_message_get_name(
    struct _cef_process_message_t* self);
extern struct _cef_list_value_t* cefingo_process_message_get_argument_list(
    struct _cef_process_message_t* self);


extern struct _cef_browser_host_t* cefingo_browser_get_host(
    struct _cef_browser_t* self);
extern struct _cef_frame_t* cefingo_browser_get_focused_frame(
    struct _cef_browser_t* self);
extern int cefingo_browser_send_process_message(
    struct _cef_browser_t* self,
    cef_process_id_t target_process,
    struct _cef_process_message_t* message);

extern void cefingo_browser_host_run_file_dialog(
    struct _cef_browser_host_t* self,
    cef_file_dialog_mode_t mode,
    const cef_string_t* title,
    const cef_string_t* default_file_path,
    cef_string_list_t accept_filters,
    int selected_accept_filter,
    struct _cef_run_file_dialog_callback_t* callback);

#endif // CEFINGO_H_