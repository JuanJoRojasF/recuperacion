#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Necesario para tolower

// --- ESTRUCTURAS ---

typedef struct {
    char nombre[50];
    char cedula[15]; 
    char direccion[50];
    char telefono[15];      
    char correo[30]; 
} Cliente;

typedef struct {
    int id;
    char nombreRepuesto[30]; 
    char descripcion[50];    
    char categoria[20];      
    float precioUnitario;
    int stock;               
} Repuesto;

typedef struct {
    int idFactura;
    char cedulaCliente[15];
    char nombreCliente[50];
    char nombreRepuesto[30];
    int cantidadComprada;
    float precioUnitario;
    float totalPagar;
} Factura;

// --- PROTOTIPOS ---

// Utilidades
void limpiarBuffer();
void leerCadena(char *cadena, int n);
int leerEntero(char* mensaje);
int leerEnteroRango(char* mensaje, int min, int max);
float leerFlotante(char* mensaje);
void convertirMinusculas(char *str, char *dest); // Nueva funcion auxiliar

// Clientes
void crearCliente();
void listarClientes();
void gestionarClientes(); // Validacion arreglada (Opcion 3)
int buscarClienteCedula(char *cedula, Cliente *cDestino);

// Inventario (Repuestos)
void inicializarInventario(); // Nueva funcion para stock automatico
void crearRepuesto();
void listarRepuestos();
void buscarRepuesto(); // Validacion arreglada (Opcion 6)
int existeIdRepuesto(int id);

// Ventas y Facturación
void realizarVenta();
void listarFacturas();

// Menú
int menu();

#endif