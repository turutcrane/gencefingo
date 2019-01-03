#include "cefingo.h"
#include "_cgo_export.h"

void cefingo_construct_life_span_handler(cefingo_life_span_handler_wrapper_t *handler) {
    // cefingo_cslogf(__func__, "L14: 0x%llx", handler);
    initialize_cefingo_base_ref_counted(
        offsetof(__typeof(*handler), counter),
        (cef_base_ref_counted_t*) handler);
    handler->body.on_before_close = cefingo_life_span_handler_on_before_close;
    handler->body.do_close = cefingo_life_span_handler_do_close;
    handler->body.on_after_created = cefingo_life_span_handler_on_after_created;
}

void cefingo_construct_browser_process_handler(cefingo_browser_process_handler_wrapper_t *handler) {
    initialize_cefingo_base_ref_counted(
        offsetof(__typeof__(*handler), counter),
        (cef_base_ref_counted_t*) handler);
    handler->body.on_context_initialized = cefingo_browser_process_handler_on_context_initialized;
}

void cefingo_construct_client(cefingo_client_wrapper_t* client) {
    initialize_cefingo_base_ref_counted(
        offsetof(__typeof__(*client), counter),
        (cef_base_ref_counted_t*) client);

//     // callbacks
    client->body.get_context_menu_handler = cefingo_client_get_context_menu_handler;
    client->body.get_dialog_handler = cefingo_client_get_dialog_handler;
    client->body.get_display_handler = cefingo_client_get_display_handler;
    client->body.get_download_handler = cefingo_client_get_download_handler;
    client->body.get_drag_handler = cefingo_client_get_drag_handler;
    client->body.get_find_handler = cefingo_client_get_find_handler;
    client->body.get_focus_handler = cefingo_client_get_focus_handler;
    client->body.get_jsdialog_handler = cefingo_client_get_jsdialog_handler;
    client->body.get_keyboard_handler = cefingo_client_get_keyboard_handler;
    client->body.get_life_span_handler = cefingo_client_get_life_span_handler;
    client->body.get_load_handler = cefingo_client_client_get_load_handler;
    client->body.get_render_handler = cefingo_client_get_render_handler;
    client->body.get_request_handler = cefingo_client_get_request_handler;
    client->body.on_process_message_received = cefingo_client_on_process_message_received;
}

typedef void(CEF_CALLBACK* cefingo_on_before_command_line_processing_t)(
      struct _cef_app_t* self,
      const cef_string_t* process_type,
      struct _cef_command_line_t* command_line);

void cefingo_construct_app(cefingo_app_wrapper_t* app) {
    initialize_cefingo_base_ref_counted(
        offsetof(__typeof__(*app), counter),
        (cef_base_ref_counted_t*) app);

    // callbacks
    app->body.on_before_command_line_processing =
     (cefingo_on_before_command_line_processing_t) cefing_app_on_before_command_line_processing;
    app->body.on_register_custom_schemes = cefing_app_on_register_custom_schemes;

    app->body.get_resource_bundle_handler = cefing_app_get_resource_bundle_handler;
    app->body.get_browser_process_handler = cefing_app_get_browser_process_handler;
    app->body.get_render_process_handler = cefing_app_get_render_process_handler;
}

void cefingo_construct_render_process_handler(cefingo_render_process_handler_wrapper_t* handler) {
    initialize_cefingo_base_ref_counted(
        offsetof(__typeof__(*handler), counter),
        (cef_base_ref_counted_t*) handler);

    // callbacks
    handler->body.on_render_thread_created = cefingo_render_process_handler_on_render_thread_created;
    handler->body.on_context_created = cefingo_render_process_handler_on_context_created;
    handler->body.on_web_kit_initialized = cefingo_render_process_handler_on_web_kit_initialized;
    handler->body.on_browser_created = cefingo_render_process_handler_on_browser_created;
    handler->body.on_browser_destroyed = cefingo_render_process_handler_on_browser_destroyed;
    handler->body.get_load_handler = cefingo_render_process_handler_get_load_handler;
    handler->body.on_context_released = cefingo_render_process_handler_on_context_released;
    handler->body.on_uncaught_exception = cefingo_render_process_handler_on_uncaught_exception;
    handler->body.on_focused_node_changed = cefingo_render_process_handler_on_focused_node_changed;
    handler->body.on_process_message_received = cefingo_render_process_handler_on_process_message_received;

}


typedef void(CEF_CALLBACK* on_load_error_t)(struct _cef_load_handler_t* self,
                                    struct _cef_browser_t* browser,
                                    struct _cef_frame_t* frame,
                                    cef_errorcode_t errorCode,
                                    const cef_string_t* errorText,
                                    const cef_string_t* failedUrl);

void cefingo_construct_load_handler(cefingo_load_handler_wrapper_t *handler) {
    initialize_cefingo_base_ref_counted(
        offsetof(__typeof__(*handler), counter),
        (cef_base_ref_counted_t*) handler);

    handler->body.on_loading_state_change = cefingo_load_handler_on_loading_state_change;
    handler->body.on_load_start = cefingo_load_handler_on_load_start;
    handler->body.on_load_end = cefingo_load_handler_on_load_end;
    handler->body.on_load_error = (on_load_error_t)cefingo_load_handler_on_load_error;
}

cef_v8context_t *cefingo_frame_get_v8context(cef_frame_t *self) {
    return self->get_v8context(self);
}

typedef struct _cef_resource_handler_t*(CEF_CALLBACK* cefingo_resource_hander_create_t)(
      struct _cef_scheme_handler_factory_t* self,
      struct _cef_browser_t* browser,
      struct _cef_frame_t* frame,
      const cef_string_t* scheme_name,
      struct _cef_request_t* request);

void cefingo_construct_scheme_handler_factory(cefingo_scheme_handler_factory_wrapper_t *factory) {
    initialize_cefingo_base_ref_counted(
        offsetof(__typeof__(*factory), counter),
        (cef_base_ref_counted_t*) factory);

        factory->body.create = (cefingo_resource_hander_create_t) cefingo_scheme_handler_factory_create;
}

int cefingo_scheme_registrar_add_custom_scheme(struct _cef_scheme_registrar_t* self,
                                       const cef_string_t* scheme_name,
                                       int is_standard,
                                       int is_local,
                                       int is_display_isolated,
                                       int is_secure,
                                       int is_cors_enabled,
                                       int is_csp_bypassing) {
    return self->add_custom_scheme(self, scheme_name,
     is_standard, is_local, is_display_isolated, is_secure, is_cors_enabled, is_csp_bypassing );
}

typedef   int(CEF_CALLBACK* can_xxx_cookie_t)(struct _cef_resource_handler_t* self,
                                    const struct _cef_cookie_t* cookie);

void cefingo_construct_resource_handler(cefingo_resource_handler_wrapper_t *handler) {
    initialize_cefingo_base_ref_counted(
        offsetof(__typeof__(*handler), counter),
        (cef_base_ref_counted_t*) handler);

        handler->body.process_request = cefingo_resource_handler_process_request;
        handler->body.get_response_headers = cefingo_resource_handler_get_response_headers;
        handler->body.read_response = cefingo_resource_handler_read_response;
        handler->body.can_get_cookie = (can_xxx_cookie_t) cefingo_resource_handler_can_get_cookie;
        handler->body.can_set_cookie = (can_xxx_cookie_t) cefingo_resource_handler_can_set_cookie;
        handler->body.cancel = cefingo_resource_handler_cancel;
}

void cefingo_callback_cont(struct _cef_callback_t* self) {
    self->cont(self);
}

void cefingo_callback_cancel(struct _cef_callback_t* self) {
    self->cancel(self);
};

void cefingo_response_set_error(struct _cef_response_t* self, cef_errorcode_t error) {
    self->set_error(self, error);
}

void cefingo_response_set_status(struct _cef_response_t* self, int status) {
    self->set_status(self, status);
}

void cefingo_response_set_status_text(struct _cef_response_t* self,
                                      const cef_string_t* statusText) {
    self->set_status_text(self, statusText);
}

void cefingo_response_set_mime_type(struct _cef_response_t* self,
                        const cef_string_t* mimeType) {
    self->set_mime_type(self, mimeType);
}

void cefingo_response_get_header_map(struct _cef_response_t* self, cef_string_multimap_t map) {
    self->get_header_map(self, map);
}

void cefingo_response_set_header_map(struct _cef_response_t* self,
                                     cef_string_multimap_t headerMap) {
    self->set_header_map(self, headerMap);
}

cef_string_userfree_t cefingo_request_get_url(struct _cef_request_t* self) {
    return self->get_url(self);
}
