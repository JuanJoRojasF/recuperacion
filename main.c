#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "funciones.h"

int main() {
    int continuar = 1;
    srand(time(NULL)); 

    // --- CARGA AUTOMATICA DE STOCK ---
    // Esto crea el archivo con repuestos si es la primera vez que se corre
    inicializarInventario(); 

    while(continuar == 1){ 
        int opc = menu();

        switch (opc) {
        case 1: crearCliente(); break;
        case 2: listarClientes(); break;
        case 3: gestionarClientes(); break; // Opcion arreglada
        case 4: crearRepuesto(); break;
        case 5: listarRepuestos(); break;
        case 6: buscarRepuesto(); break; // Opcion arreglada
        case 7: realizarVenta(); break;
        case 8: listarFacturas(); break;
        case 9: 
            continuar = 0; 
            break;
        }

        if (continuar != 0) {
            printf("\n");
            // Mantenemos la terminal sin borrar (sin cls) como pediste
            continuar = leerEnteroRango("Desea realizar otra operacion? (1.Si / 2.No): ", 1, 2);
            printf("\n--------------------------------------------\n");
        }
    }

    printf("Saliendo del sistema...\n");
    printf("Presione Enter para cerrar...");
    getchar(); 
    if(getchar() != '\n') getchar(); 

    return 0;
}