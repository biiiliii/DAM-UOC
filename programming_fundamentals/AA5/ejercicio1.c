#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#define MAX_VEHICULOS 500

typedef struct {
  char matricula[9];
  char combustible[10];
  float kilometraje;

  struct tm fecha_adquisicion;
  float costo_adquisicion;
  bool estado_operativo;
} tVehiculo;

typedef struct {
    char nombre_empresa[50];
    int codigo_postal;
    char telefono_contacto[15];
    tVehiculo vehiculos[MAX_VEHICULOS];
    int cantidad_vehiculos;
} tFlota;

void mostrar_menu();
void dar_alta_flota(tFlota *flota);
void dar_alta_vehiculo(tFlota *flota);
void borrar_vehiculo(tFlota *flota);
void modificar_vehiculo(tFlota *flota);
void listar_vehiculos(tFlota *flota);
void listar_vehiculos_por_kilometraje(tFlota *flota, float kilometros);
void listar_vehiculos_por_anio(tFlota *flota, int anio);
float calcular_mejor_ratio(tFlota *flota);
int contar_vehiculos_por_kilometraje(tFlota *flota, float kilometros);

int main() {
    tFlota flota;
    int opcion;
    do {
        mostrar_menu();
        printf("Ingrese una opción: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                dar_alta_flota(&flota);
                break;
            case 2:
                dar_alta_vehiculo(&flota);
                break;
            case 3:
                borrar_vehiculo(&flota);
                break;
            case 4:
                modificar_vehiculo(&flota);
                break;
            case 5:
                listar_vehiculos(&flota);
                break;
            case 6: {
                float kilometros;
                printf("Ingrese el kilometraje: ");
                scanf("%f", &kilometros);
                listar_vehiculos_por_kilometraje(&flota, kilometros);
                break;
            }
            case 7: {
                int anio;
                printf("Ingrese el año: ");
                scanf("%d", &anio);
                listar_vehiculos_por_anio(&flota, anio);
                break;
            }
            case 8:
                printf("Saliendo del menú.\n");
                break;
            default:
                printf("Opción no válida.\n");
                break;
        }
    } while (opcion != 8);
    return 0;
}

float calcular_mejor_ratio(tFlota *flota) {
    float mejor_ratio = 0.0;
    for (int i = 0; i < flota->cantidad_vehiculos; i++) {
        tVehiculo vehiculo = flota->vehiculos[i];
        if (vehiculo.costo_adquisicion > 0) {
            float ratio = vehiculo.kilometraje / vehiculo.costo_adquisicion;
            if (ratio > mejor_ratio) {
                mejor_ratio = ratio;
            }
        }
    }
    return mejor_ratio;
}

int contar_vehiculos_por_kilometraje(tFlota *flota, float kilometros) {
    int contador = 0;
    for (int i = 0; i < flota->cantidad_vehiculos; i++) {
        if (flota->vehiculos[i].kilometraje > kilometros) {
            contador++;
        }
    }
    return contador;
}

void dar_alta_flota(tFlota *flota) {
    printf("Ingrese el nombre de la empresa: ");
    scanf("%s", flota->nombre_empresa);
    printf("Ingrese el código postal: ");
    scanf("%d", &flota->codigo_postal);
    printf("Ingrese el teléfono de contacto: ");
    scanf("%s", flota->telefono_contacto);
    flota->cantidad_vehiculos = 0;
}

void dar_alta_vehiculo(tFlota *flota) {
    if (flota->cantidad_vehiculos >= MAX_VEHICULOS) {
        printf("No se pueden agregar más vehículos.\n");
        return;
    }
    tVehiculo *vehiculo = &flota->vehiculos[flota->cantidad_vehiculos];
    printf("Ingrese la matrícula: ");
    scanf("%s", vehiculo->matricula);
    printf("Ingrese el tipo de combustible: ");
    scanf("%s", vehiculo->combustible);
    printf("Ingrese el kilometraje: ");
    scanf("%f", &vehiculo->kilometraje);
    printf("Ingrese la fecha de adquisición (dd mm yyyy): ");
    int dia, mes, anio;
    scanf("%d %d %d", &dia, &mes, &anio);
    vehiculo->fecha_adquisicion.tm_mday = dia;
    vehiculo->fecha_adquisicion.tm_mon = mes - 1;
    vehiculo->fecha_adquisicion.tm_year = anio - 1900;
    printf("Ingrese el costo de adquisición: ");
    scanf("%f", &vehiculo->costo_adquisicion);
    vehiculo->estado_operativo = true;
    flota->cantidad_vehiculos++;
}

void borrar_vehiculo(tFlota *flota) {
    char matricula[9];
    printf("Ingrese la matrícula del vehículo a borrar: ");
    scanf("%s", matricula);
    for (int i = 0; i < flota->cantidad_vehiculos; i++) {
        if (strcmp(flota->vehiculos[i].matricula, matricula) == 0) {
            for (int j = i; j < flota->cantidad_vehiculos - 1; j++) {
                flota->vehiculos[j] = flota->vehiculos[j + 1];
            }
            flota->cantidad_vehiculos--;
            printf("Vehículo borrado.\n");
            return;
        }
    }
    printf("Vehículo no encontrado.\n");
}

void modificar_vehiculo(tFlota *flota) {
    char matricula[9];
    printf("Ingrese la matrícula del vehículo a modificar: ");
    scanf("%s", matricula);
    for (int i = 0; i < flota->cantidad_vehiculos; i++) {
        if (strcmp(flota->vehiculos[i].matricula, matricula) == 0) {
            tVehiculo *vehiculo = &flota->vehiculos[i];
            printf("Ingrese el nuevo tipo de combustible: ");
            scanf("%s", vehiculo->combustible);
            printf("Ingrese el nuevo kilometraje: ");
            scanf("%f", &vehiculo->kilometraje);
            printf("Ingrese la nueva fecha de adquisición (dd mm yyyy): ");
            int dia, mes, anio;
            scanf("%d %d %d", &dia, &mes, &anio);
            vehiculo->fecha_adquisicion.tm_mday = dia;
            vehiculo->fecha_adquisicion.tm_mon = mes - 1;
            vehiculo->fecha_adquisicion.tm_year = anio - 1900;
            printf("Ingrese el nuevo costo de adquisición: ");
            scanf("%f", &vehiculo->costo_adquisicion);
            printf("Ingrese el nuevo estado operativo (1 para operativo, 0 para no operativo): ");
            int estado;
            scanf("%d", &estado);
            vehiculo->estado_operativo = estado;
            printf("Vehículo modificado.\n");
            return;
        }
    }
    printf("Vehículo no encontrado.\n");
}

void listar_vehiculos(tFlota *flota) {
    for (int i = 0; i < flota->cantidad_vehiculos; i++) {
        tVehiculo vehiculo = flota->vehiculos[i];
        printf("Matrícula: %s, Combustible: %s, Kilometraje: %.2f, Fecha de adquisición: %02d/%02d/%04d, Costo de adquisición: %.2f, Estado operativo: %s\n",
               vehiculo.matricula, vehiculo.combustible, vehiculo.kilometraje,
               vehiculo.fecha_adquisicion.tm_mday, vehiculo.fecha_adquisicion.tm_mon + 1, vehiculo.fecha_adquisicion.tm_year + 1900,
               vehiculo.costo_adquisicion, vehiculo.estado_operativo ? "Operativo" : "No operativo");
    }
}

void listar_vehiculos_por_kilometraje(tFlota *flota, float kilometros) {
    for (int i = 0; i < flota->cantidad_vehiculos; i++) {
        if (flota->vehiculos[i].kilometraje > kilometros) {
            tVehiculo vehiculo = flota->vehiculos[i];
            printf("Matrícula: %s, Combustible: %s, Kilometraje: %.2f, Fecha de adquisición: %02d/%02d/%04d, Costo de adquisición: %.2f, Estado operativo: %s\n",
                   vehiculo.matricula, vehiculo.combustible, vehiculo.kilometraje,
                   vehiculo.fecha_adquisicion.tm_mday, vehiculo.fecha_adquisicion.tm_mon + 1, vehiculo.fecha_adquisicion.tm_year + 1900,
                   vehiculo.costo_adquisicion, vehiculo.estado_operativo ? "Operativo" : "No operativo");
        }
    }
}

void listar_vehiculos_por_anio(tFlota *flota, int anio) {
    for (int i = 0; i < flota->cantidad_vehiculos; i++) {
        if (flota->vehiculos[i].fecha_adquisicion.tm_year + 1900 == anio) {
            tVehiculo vehiculo = flota->vehiculos[i];
            printf("Matrícula: %s, Combustible: %s, Kilometraje: %.2f, Fecha de adquisición: %02d/%02d/%04d, Costo de adquisición: %.2f, Estado operativo: %s\n",
                   vehiculo.matricula, vehiculo.combustible, vehiculo.kilometraje,
                   vehiculo.fecha_adquisicion.tm_mday, vehiculo.fecha_adquisicion.tm_mon + 1, vehiculo.fecha_adquisicion.tm_year + 1900,
                   vehiculo.costo_adquisicion, vehiculo.estado_operativo ? "Operativo" : "No operativo");
        }
    }
}

void mostrar_menu() {
    printf("1. Dar de alta una flota\n");
    printf("2. Dar de alta un vehículo en una flota\n");
    printf("3. Borrar un vehículo de una flota\n");
    printf("4. Modificar los datos de un vehículo de una flota\n");
    printf("5. Listar los vehículos de una flota\n");
    printf("6. Listar los vehículos que superen los kilómetros introducidos por el usuario\n");
    printf("7. Listar los vehículos para un año facilitado por el usuario\n");
    printf("8. Salir del menú\n");
}