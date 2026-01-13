#include "funciones.h"



void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void leerCadena(char *cadena, int n){
    fgets(cadena, n, stdin);
    size_t len = strlen(cadena);
    if (len > 0 && cadena[len - 1] == '\n') {
        cadena[len - 1] = '\0';
    } else {
        
    }
}

int leerEnteroRango(char* mensaje, int min, int max) {
    int valor;
    int resultado;
    do {
        printf("%s", mensaje);
        resultado = scanf("%d", &valor);
        limpiarBuffer();
        if (resultado != 1 || valor < min || valor > max) {
            printf("[!] Error: Ingrese un numero entre %d y %d.\n", min, max);
        }
    } while (resultado != 1 || valor < min || valor > max);
    return valor;
}

float leerFlotante(char* mensaje) {
    float valor;
    int resultado;
    do {
        printf("%s", mensaje);
        resultado = scanf("%f", &valor);
        limpiarBuffer();
        if (resultado != 1 || valor < 0) {
            printf("[!] Error: Ingrese un valor numerico positivo.\n");
        }
    } while (resultado != 1 || valor < 0);
    return valor;
}


void convertirMinusculas(char *src, char *dest) {
    int i = 0;
    while(src[i]) {
        dest[i] = tolower(src[i]);
        i++;
    }
    dest[i] = '\0';
}

int menu(){
    printf("\n============================================\n");
    printf("   SISTEMA DE REPUESTOS 'AUTOPARTES PRO'   \n");
    printf("============================================\n");
    printf("1. Nuevo Cliente\n");
    printf("2. Ver Clientes\n");
    printf("3. Modificar/Eliminar Cliente\n");
    printf("4. Ingresar Nuevo Repuesto (Manual)\n");
    printf("5. Ver Inventario (Stock)\n");
    printf("6. Buscar Repuesto\n");
    printf("7. VENDER REPUESTO (Facturacion)\n");
    printf("8. Historial de Ventas\n");
    printf("9. Salir\n");
    return leerEnteroRango(">> Seleccione opcion: ", 1, 9);
}



void inicializarInventario() {
    FILE *f = fopen("inventario.dat", "rb");
    if(f) {
        
        fclose(f);
        return;
    }

    
    f = fopen("inventario.dat", "wb");
    if(!f) return;

    Repuesto lista[] = {
        {101, "Aceite Sintetico 5W-30", "Galon 4L para motor gasolina", "Motor", 45.50, 20},
        {102, "Filtro de Aire", "Toyota Corolla/Yaris", "Filtros", 12.00, 15},
        {103, "Pastillas de Freno", "Ceramica Delanteras Universal", "Frenos", 35.00, 10},
        {104, "Bateria 12V", "600 Amperios Libre Mantenimiento", "Electrico", 120.00, 5},
        {105, "Amortiguador Trasero", "Suspension Hidraulica", "Suspension", 80.00, 8},
        {106, "Bujias Iridio", "Pack de 4 unidades", "Motor", 28.00, 25}
    };

    fwrite(lista, sizeof(Repuesto), 6, f); 
    fclose(f);
    printf("\n[SISTEMA] Inventario inicializado con datos por defecto.\n");
}



void crearCliente(){
    Cliente c;
    FILE *f = fopen("clientes.dat","ab");
    if(!f) { printf("Error de archivo.\n"); return; }

    printf("\n--- REGISTRO DE CLIENTE ---\n");
    printf("Nombre Completo: "); leerCadena(c.nombre, 50);
    printf("Cedula/DNI: "); leerCadena(c.cedula, 15);
    printf("Direccion: "); leerCadena(c.direccion, 50);
    printf("Telefono: "); leerCadena(c.telefono, 15);
    printf("Correo: "); leerCadena(c.correo, 30);

    fwrite(&c, sizeof(Cliente), 1, f);
    fclose(f);
    printf(">> Cliente guardado correctamente.\n");
}

void listarClientes(){
    Cliente c;
    FILE *f = fopen("clientes.dat","rb");
    if(!f) { printf("[!] No hay clientes registrados.\n"); return; }

    printf("\n%-15s %-25s %-15s\n", "CEDULA", "NOMBRE", "TELEFONO");
    printf("----------------------------------------------------------\n");
    while(fread(&c, sizeof(Cliente), 1, f)){
        printf("%-15s %-25s %-15s\n", c.cedula, c.nombre, c.telefono);
    }
    fclose(f);
}

int buscarClienteCedula(char *cedula, Cliente *cDestino){
    FILE *f = fopen("clientes.dat", "rb");
    if(!f) return 0;
    
    Cliente c;
    while(fread(&c, sizeof(Cliente), 1, f)){
        if(strcmp(c.cedula, cedula) == 0){
            *cDestino = c;
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

void gestionarClientes(){
    char cedula[15];
    int encontrado = 0;
    int opcion;
    Cliente c;
    FILE *f = fopen("clientes.dat", "rb");
    FILE *tmp = fopen("tmp_cli.dat", "wb");

    if(!f || !tmp) {
        printf("Error al abrir archivos. Asegurese de tener clientes registrados.\n");
        if(f) fclose(f);
        if(tmp) fclose(tmp);
        return;
    }

    printf("\nIngrese CEDULA del cliente a buscar: ");
    leerCadena(cedula, 15);

    while(fread(&c, sizeof(Cliente), 1, f)){
        if(strcmp(c.cedula, cedula) == 0){
            encontrado = 1;
            printf("\nCLIENTE ENCONTRADO:\n");
            printf("Nombre: %s | Tel: %s | Dir: %s\n", c.nombre, c.telefono, c.direccion);
            printf("-------------------------------\n");
            printf("1. Modificar Datos\n");
            printf("2. Eliminar Cliente\n");
            printf("3. Cancelar\n");
            opcion = leerEnteroRango(">> Opcion: ", 1, 3);

            if(opcion == 1){
                
                printf("\n--- Ingrese Nuevos Datos ---\n");
                printf("Nuevo Nombre: "); leerCadena(c.nombre, 50);
                printf("Nueva Direccion: "); leerCadena(c.direccion, 50);
                printf("Nuevo Telefono: "); leerCadena(c.telefono, 15);
                printf("Nuevo Correo: "); leerCadena(c.correo, 30);
                fwrite(&c, sizeof(Cliente), 1, tmp);
                printf(">> Cliente modificado exitosamente.\n");
            } 
            else if (opcion == 2) {
                
                int confirm;
                confirm = leerEnteroRango("Seguro que desea eliminar? 1.Si / 2.No: ", 1, 2);
                if(confirm == 2){
                     fwrite(&c, sizeof(Cliente), 1, tmp); 
                     printf(">> Eliminacion cancelada.\n");
                } else {
                     printf(">> Cliente eliminado permanentemente.\n");
                }
            } 
            else {
                
                fwrite(&c, sizeof(Cliente), 1, tmp);
            }

        } else {
            
            fwrite(&c, sizeof(Cliente), 1, tmp);
        }
    }
    fclose(f);
    fclose(tmp);

    if(encontrado){
        remove("clientes.dat");
        rename("tmp_cli.dat", "clientes.dat");
    } else {
        remove("tmp_cli.dat");
        printf("[!] Cliente con cedula %s no encontrado.\n", cedula);
    }
}



int existeIdRepuesto(int id){
    FILE *f = fopen("inventario.dat", "rb");
    if(!f) return 0;
    Repuesto r;
    while(fread(&r, sizeof(Repuesto), 1, f)){
        if(r.id == id){
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

void crearRepuesto(){
    Repuesto r;
    FILE *f = fopen("inventario.dat","ab");
    if(!f) return;

    printf("\n--- ALTA DE REPUESTO MANUAL ---\n");
    do {
        r.id = leerEnteroRango("ID del Repuesto (1-9999): ", 1, 9999);
        if(existeIdRepuesto(r.id)) printf("[!] El ID ya existe. Use otro.\n");
    } while(existeIdRepuesto(r.id));

    printf("Nombre Repuesto: "); leerCadena(r.nombreRepuesto, 30);
    printf("Descripcion: "); leerCadena(r.descripcion, 50);
    printf("Categoria: "); leerCadena(r.categoria, 20);
    r.precioUnitario = leerFlotante("Precio Unitario ($): ");
    r.stock = leerEnteroRango("Stock Inicial: ", 0, 10000);

    fwrite(&r, sizeof(Repuesto), 1, f);
    fclose(f);
    printf(">> Repuesto agregado.\n");
}

void listarRepuestos(){
    Repuesto r;
    FILE *f = fopen("inventario.dat","rb");
    if(!f) { printf("[!] Inventario vacio.\n"); return; }

    printf("\n%-6s %-25s %-10s %-6s %-15s\n", "ID", "NOMBRE", "PRECIO", "STOCK", "CATEGORIA");
    printf("------------------------------------------------------------------------\n");
    while(fread(&r, sizeof(Repuesto), 1, f)){
        printf("%-6d %-25.25s $%-9.2f %-6d %-15.15s\n", r.id, r.nombreRepuesto, r.precioUnitario, r.stock, r.categoria);
    }
    fclose(f);
}


void buscarRepuesto(){
    char termino[30];
    char terminoMin[30];
    char nombreMin[30];
    char catMin[30];
    Repuesto r;
    int matches = 0;
    
    printf("\n--- BUSQUEDA DE REPUESTO ---\n");
    printf("Ingrese nombre o categoria (Ej: frenos): ");
    leerCadena(termino, 30);
    
   
    convertirMinusculas(termino, terminoMin);

    FILE *f = fopen("inventario.dat", "rb");
    if(!f) { printf("Inventario vacio.\n"); return; }

    printf("\n%-6s %-25s %-10s %-30s\n", "ID", "NOMBRE", "PRECIO", "DESCRIPCION");
    printf("--------------------------------------------------------------------------\n");
    
    while(fread(&r, sizeof(Repuesto), 1, f)){
        // Convertir datos del archivo a minusculas temporalmente para comparar
        convertirMinusculas(r.nombreRepuesto, nombreMin);
        convertirMinusculas(r.categoria, catMin);

        // Buscar si el termino esta contenido en nombre o categoria
        if(strstr(nombreMin, terminoMin) != NULL || strstr(catMin, terminoMin) != NULL){
            printf("%-6d %-25s $%-9.2f %-30s\n", 
                   r.id, r.nombreRepuesto, r.precioUnitario, r.descripcion);
            matches++;
        }
    }
    printf("--------------------------------------------------------------------------\n");
    if(matches == 0) printf("No se encontraron coincidencias para '%s'.\n", termino);
    else printf("Total encontrados: %d\n", matches);
    
    fclose(f);
}

// --- VENTAS Y FACTURACIÓN ---

void realizarVenta(){
    char cedula[15];
    Cliente cliente;
    Repuesto rep;
    Factura fact;
    int idProd, cantidad;
    int ventaExitosa = 0;

    printf("\n--- NUEVA VENTA ---\n");
    printf("Ingrese Cedula del Cliente: ");
    leerCadena(cedula, 15);

    if(!buscarClienteCedula(cedula, &cliente)){
        printf("[!] Cliente no registrado. Registrelo en la opcion 1.\n");
        return;
    }
    printf(">> Cliente: %s\n", cliente.nombre);

    listarRepuestos(); // Mostramos el stock disponible
    
    FILE *fInv = fopen("inventario.dat", "rb");
    FILE *tmpInv = fopen("tmp_inv.dat", "wb");
    if(!fInv || !tmpInv) return;

    idProd = leerEnteroRango("\nIngrese ID del Repuesto a vender: ", 1, 9999);
    int prodEncontrado = 0;

    while(fread(&rep, sizeof(Repuesto), 1, fInv)){
        if(rep.id == idProd){
            prodEncontrado = 1;
            printf("Seleccionado: %s | Stock: %d | Precio: $%.2f\n", rep.nombreRepuesto, rep.stock, rep.precioUnitario);
            
            if(rep.stock == 0) {
                printf("[!] Este producto esta AGOTADO.\n");
                fwrite(&rep, sizeof(Repuesto), 1, tmpInv); // Se guarda igual
            } else {
                cantidad = leerEnteroRango("Cantidad a comprar: ", 1, 1000);
                
                if(cantidad <= rep.stock){
                    // Operacion de venta
                    rep.stock -= cantidad;
                    
                    // Llenar factura
                    fact.idFactura = rand() % 90000 + 10000;
                    strcpy(fact.cedulaCliente, cliente.cedula);
                    strcpy(fact.nombreCliente, cliente.nombre);
                    strcpy(fact.nombreRepuesto, rep.nombreRepuesto);
                    fact.cantidadComprada = cantidad;
                    fact.precioUnitario = rep.precioUnitario;
                    fact.totalPagar = cantidad * rep.precioUnitario;
                    
                    ventaExitosa = 1;
                    fwrite(&rep, sizeof(Repuesto), 1, tmpInv); // Guardar actualizado
                } else {
                    printf("[!] Stock insuficiente (Solo hay %d).\n", rep.stock);
                    fwrite(&rep, sizeof(Repuesto), 1, tmpInv); // Guardar sin cambios
                }
            }
        } else {
            fwrite(&rep, sizeof(Repuesto), 1, tmpInv); // Copiar el resto
        }
    }

    fclose(fInv);
    fclose(tmpInv);

    if(!prodEncontrado){
        remove("tmp_inv.dat");
        printf("[!] ID no existe.\n");
        return;
    }

    remove("inventario.dat");
    rename("tmp_inv.dat", "inventario.dat");

    if(ventaExitosa){
        FILE *fFact = fopen("facturas.dat", "ab");
        if(fFact){
            fwrite(&fact, sizeof(Factura), 1, fFact);
            fclose(fFact);
            printf("\n>>> VENTA REALIZADA <<<\n");
            printf("Cliente: %s\n", fact.nombreCliente);
            printf("Producto: %s x %d\n", fact.nombreRepuesto, fact.cantidadComprada);
            printf("TOTAL: $%.2f\n", fact.totalPagar);
        }
    }
}

void listarFacturas(){
    Factura ft;
    FILE *f = fopen("facturas.dat", "rb");
    if(!f) { printf("[!] No hay historial de ventas.\n"); return; }

    printf("\n%-6s %-15s %-20s %-5s %-10s\n", "ID", "CLIENTE", "REPUESTO", "CANT", "TOTAL");
    printf("----------------------------------------------------------------\n");
    float granTotal = 0;
    while(fread(&ft, sizeof(Factura), 1, f)){
        printf("%-6d %-15.15s %-20.20s %-5d $%-9.2f\n", 
            ft.idFactura, ft.nombreCliente, ft.nombreRepuesto, ft.cantidadComprada, ft.totalPagar);
        granTotal += ft.totalPagar;
    }
    printf("----------------------------------------------------------------\n");
    printf("INGRESOS TOTALES: $%.2f\n", granTotal);
    fclose(f);
}