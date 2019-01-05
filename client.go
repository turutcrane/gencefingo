package cefingo

import (
	"log"
	"unsafe"
)

// #include "cefingo.h"
import "C"

// Client is Go interface of C.cef_client_t
type Client interface {
	///
	// Called when a new message is received from a different process. Return true
	// (1) if the message was handled or false (0) otherwise. Do not keep a
	// reference to or attempt to access the message outside of this callback.
	// https://github.com/chromiumembedded/cef/blob/3497/include/capi/cef_client_capi.h#L154-L164
	///
	OnProcessMessageRecived(self *CClientT,
		browser *CBrowserT,
		source_process CProcessIdT,
		message *CProcessMessageT,
	) bool
}

var client_method = map[*CClientT]Client{}
var life_span_handler = map[*CClientT]*CLifeSpanHandlerT{}

// AllocCClient allocates CClientT and construct it
func AllocCClient(c Client) (cClient *CClientT) {
	p := C.calloc(1, C.sizeof_cefingo_client_wrapper_t)
	Logf("L26: p: %v", p)
	C.cefingo_construct_client((*C.cefingo_client_wrapper_t)(p))

	cClient = (*CClientT)(p)
	BaseAddRef(cClient)
	client_method[cClient] = c

	return cClient
}

///
// Return the handler for context menus. If no handler is
// provided the default implementation will be used.
///
//export cefingo_client_get_context_menu_handler
func cefingo_client_get_context_menu_handler(self *CClientT) *CContextMenuHandlerT {
	return nil
}

///
// Return the handler for dialogs. If no handler is provided the default
// implementation will be used.
///
//export cefingo_client_get_dialog_handler
func cefingo_client_get_dialog_handler(self *CClientT) *CDialogHandlerT {
	return nil
}

///
// Return the handler for browser display state events.
///
//export cefingo_client_get_display_handler
func cefingo_client_get_display_handler(self *CClientT) *CDisplayHandlerT {
	return nil
}

///
// Return the handler for download events. If no handler is returned downloads
// will not be allowed.
///
//export cefingo_client_get_download_handler
func cefingo_client_get_download_handler(self *CClientT) *CDownloaddHanderT {
	return nil
}

///
// Return the handler for drag events.
///
//export cefingo_client_get_drag_handler
func cefingo_client_get_drag_handler(self *CClientT) *CDragHandlerT {
	return nil
}

///
// Return the handler for find result events.
///
//export cefingo_client_get_find_handler
func cefingo_client_get_find_handler(self *CClientT) *CFindHandlerT {
	return nil
}

///
// Return the handler for focus events.
///
//export cefingo_client_get_focus_handler
func cefingo_client_get_focus_handler(self *CClientT) *CFocusHanderT {
	return nil
}

///
// Return the handler for JavaScript dialogs. If no handler is provided the
// default implementation will be used.
///
//export cefingo_client_get_jsdialog_handler
func cefingo_client_get_jsdialog_handler(self *CClientT) *CJsdialogHandlerT {
	return nil
}

///
// Return the handler for keyboard events.
///
//export cefingo_client_get_keyboard_handler
func cefingo_client_get_keyboard_handler(self *CClientT) *CKeyboardHandlerT {
	return nil
}

// AssocLifeSpanHandler associate hander to client
func (client *CClientT) AssocLifeSpanHandler(handler *CLifeSpanHandlerT) {
	BaseAddRef(handler)
	life_span_handler[client] = handler
}

///
// Return the handler for browser life span events.
///
//export cefingo_client_get_life_span_handler
func cefingo_client_get_life_span_handler(self *CClientT) *CLifeSpanHandlerT {
	Logf("L70:")

	handler := life_span_handler[self]
	if handler == nil {
		Logf("L77: No Life Span Handler")
	} else {
		p := (unsafe.Pointer)(handler)
		C.cefingo_add_ref((*C.cef_base_ref_counted_t)(p))
	}
	return handler
}

///
// Return the handler for browser load status events.
///
//export cefingo_client_client_get_load_handler
func cefingo_client_client_get_load_handler(self *CClientT) *CLoadHandlerT {
	return nil
}

///
// Return the handler for off-screen rendering events.
///
//export cefingo_client_get_render_handler
func cefingo_client_get_render_handler(self *CClientT) *CRenderHandlerT {
	return nil
}

///
// Return the handler for browser request events.
///
//export cefingo_client_get_request_handler
func cefingo_client_get_request_handler(self *CClientT) *CRequestHandlerT {
	return nil
}

//on_process_mesage_received call OnProcessMessageRecived method
//export cefingo_client_on_process_message_received
func cefingo_client_on_process_message_received(
	self *CClientT,
	browser *CBrowserT,
	source_process CProcessIdT,
	message *CProcessMessageT,
) (ret C.int) {

	Logf("L46: client: %p", self)
	f := client_method[self]
	if f == nil {
		log.Panicln("L48: on_process_message_received: Noo!")
	}

	if f.OnProcessMessageRecived(self, browser, source_process, message) {
		ret = 1
	} else {
		ret = 0
	}
	return ret
}

// DefaultClient is dummy implementation of CClientT
type DefaultClient struct {
}

func (*DefaultClient) OnProcessMessageRecived(self *CClientT,
	browser *CBrowserT,
	source_process CProcessIdT,
	message *CProcessMessageT,
) bool {
	return false
}