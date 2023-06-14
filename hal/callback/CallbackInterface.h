#ifndef MBED_CALLBACK_H_C_INTERFACE
#define MBED_CALLBACK_H_C_INTERFACE

#ifdef __cplusplus
extern "C" {
#endif

// Definición de puntero a clase Callback de C++
typedef void CallbackCpp;
typedef void AttachCallbackCpp;

typedef struct CallbackWrapper CallbackWrapper;

// Funciones de creación y destrucción de Callback
CallbackWrapper* callback_create(void (*func)());

void callback_destroy(CallbackCpp* callback);

// Función para llamar al Callback
void callback_call(CallbackWrapper* cb);


// Función para adjuntar un Callback a otro Callback
AttachCallbackCpp* attach_create(CallbackCpp* callback, float t);
void attach_destroy(AttachCallbackCpp* attachCallback);

#ifdef __cplusplus
}
#endif

#endif