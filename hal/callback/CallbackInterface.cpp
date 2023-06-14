#include "CallbackInterface.h"
#include "Callback.h"

extern "C" {


typedef struct {
    mbed::Callback<void()> callback;
    float t;
} AttachCallback;

struct CallbackWrapper {
    mbed::Callback<void()> *callback;
};

// Función de creación de Callback
CallbackWrapper* callback_create(void (*func)()) {
    //return new mbed::Callback<void()>(func);
    CallbackWrapper* wrapper = new CallbackWrapper;
    wrapper->callback = new mbed::Callback<void()>(func);
    return wrapper;
}

// Función de destrucción de Callback
void callback_destroy(CallbackCpp* callback) {
    delete static_cast<mbed::Callback<void()>*>(callback);
}

// Función para llamar al Callback
void callback_call(CallbackWrapper* cb) {
    (*cb->callback)();
}

// Función para adjuntar un Callback a otro Callback
AttachCallbackCpp* attach_create(CallbackCpp* callback, float t) {
    AttachCallback* attachCallback = new AttachCallback;
    attachCallback->callback = *static_cast<mbed::Callback<void()>*>(callback);
    attachCallback->t = t;
    return static_cast<AttachCallbackCpp*>(attachCallback);
}

// Función para destruir la estructura de AttachCallback
void attach_destroy(AttachCallbackCpp* attachCallback) {
    AttachCallback* attach = static_cast<AttachCallback*>(attachCallback);
    delete attach;
}

} 