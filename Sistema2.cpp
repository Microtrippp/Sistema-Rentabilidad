#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;

// ESTRUCTURAS DEL SISTEMA

// Estrutura para solicitar los datos de gastos fijos y variables. (nombre, costo)
struct Gastos
{
    string nombre;
    double monto;
};

// Estructura para solicitar la identidad del negocio. (nombre, sector, producto)
struct IdentidadNegocio
{
    string nombre;
    string sector;
    string servicio;
};

// Estructura para solicitar las finanzas básicas del negocio. (capital, precio de productos, cantidad de productos, gastos)
struct FinanzasBase
{
    double capitalInicial;
    double precioUnd;
    int cantidadUnidades;

    vector<Gastos> gastosFijos;
    vector<Gastos> gastosVariables;
};

// FUNCIONES DEL SISTEMA

// Función que asegura que se ingrese un valor numérico, para números decimales.
double RellenarDouble(string mensaje, int _vmin, int _vmax)
{
    double valor;
    while (true)
    {
        cout << mensaje;
        if ((cin >> valor) && (valor >= _vmin) && (valor <= _vmax))
        {
            cin.ignore();
            return valor;
        }
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nEstimado Usuario. Por favor, ingrese un numero entre " << _vmin << " y " << _vmax << "." << endl;
    }
}

// Función que asegura que se ingrese un valor numérico, para números enteros.
int RellenarInt(string mensaje, int vmin, int vmax)
{
    int valor;
    while (true)
    {
        cout << mensaje;
        if ((cin >> valor) && (valor >= vmin) && (valor <= vmax))
        {
            cin.ignore();
            return valor;
        }
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nEstimado Usuario. Por favor, ingrese un numero entre " << vmin << " y " << vmax << "." << endl;
    }
}

// Función que asegura que se rellene algún campo.
string RellenarString(string mensaje)
{
    string valor;
    while (true)
    {
        cout << mensaje;
        getline(cin, valor);
        if (!valor.empty())
        {
            return valor;
        }
        cout << "\nEstimado Usuario. Por favor, rellene este campo." << endl;
    }
}

// Función donde se rellenan los datos de la identidad del negocio.
IdentidadNegocio RellenarIdentidadNegocio()
{
    IdentidadNegocio identidad;
    cout << "\n----------------------------- DATOS DEL NEGOCIO -----------------------------" << endl;
    identidad.nombre = RellenarString("Nombre del negocio: ");
    identidad.sector = RellenarString("Sector o rubro: ");
    identidad.servicio = RellenarString("Producto o servicio principal: ");
    return identidad;
}

// Función donde se rellenan las finanzas básicas del negocio.
FinanzasBase RellenarFinanzasBase()
{

    FinanzasBase finanzas;
    cout << "\n------------------------------ BALANCE BASICO -------------------------------" << endl;
    finanzas.capitalInicial = RellenarDouble("Capital Inicial: $ ", 10, 1000000000);
    finanzas.precioUnd = RellenarDouble("Precio de Venta por Unidad: $ ", 0.001, 1000000);
    finanzas.cantidadUnidades = RellenarInt("Cantidad de Unidades Estimadas a Vender (Mensual):", 1, 1000000000);

    int numGastosFijos = RellenarInt("Cantidad de Gastos Fijos que posee (1-10): ", 1, 10);
    finanzas.gastosFijos.reserve(numGastosFijos);
    for (int i = 0; i < numGastosFijos; ++i)
    {
        Gastos gasto;
        cout << "Gasto Fijo " << (i + 1) << endl;
        gasto.nombre = RellenarString(" Ingrese el nombre del gasto fijo : ");
        gasto.monto = RellenarDouble(" Ingrese el monto del gasto fijo  : ", 0.001, 1000000);
        finanzas.gastosFijos.push_back(gasto);
    }

    int numGastosVariables = RellenarInt("Cantidad de Gastos Variables unitarios que posee (0-20): ", 0, 20);
    finanzas.gastosVariables.reserve(numGastosVariables);
    for (int i = 0; i < numGastosVariables; ++i)
    {
        Gastos gasto;
        cout << "Gasto Variable " << (i + 1) << endl;
        gasto.nombre = RellenarString(" Ingrese el nombre del gasto variable : ");
        gasto.monto = RellenarDouble(" Ingrese el monto del gasto variable  : ", 0.001, 1000000);
        finanzas.gastosVariables.push_back(gasto);
    }

    return finanzas;
}

// Función que muestra todos los datos del negocio y muestra si esta en ganancia o pérdida.
void MostrarDashboard(const IdentidadNegocio &identidad, const FinanzasBase &finanzas)
{
    // 1. Cálculos de Costos e Ingresos Base
    double totalGF = 0;
    for (int i = 0; i < finanzas.gastosFijos.size(); i++)
    {
        totalGF += finanzas.gastosFijos[i].monto;
    }

    double totalGastosVariablesUnitarios = 0;
    for (int i = 0; i < finanzas.gastosVariables.size(); i++)
    {
        totalGastosVariablesUnitarios += finanzas.gastosVariables[i].monto;
    }

    double ingresosTotales = finanzas.precioUnd * finanzas.cantidadUnidades;
    double costoVarUnd = totalGastosVariablesUnitarios * finanzas.cantidadUnidades;
    double costosTotales = totalGF + costoVarUnd;
    double utilidadNeta = ingresosTotales - costosTotales;

    // 3. Impresión del Dashboard en Consola
    cout << "\n------------------------  DASHBOARD DE RENTABILIDAD  ------------------------" << endl;
    cout << " DATOS DEL NEGOCIO" << endl;
    cout << " Empresa  : " << identidad.nombre << endl;
    cout << " Sector   : " << identidad.sector << endl;
    cout << " Producto : " << identidad.servicio << endl;
    cout << "-----------------------------------------------------------------------------" << endl;
    cout << " BALANCE DEL NEGOCIO" << endl;
    cout << " - Ingresos Totales     : $ " << ingresosTotales << endl;
    cout << " - Costos Fijos Totales : $ " << totalGF << endl;
    cout << " - Costos Variables     : $ " << costoVarUnd << endl;
    cout << " - Costos Totales       : $ " << costosTotales << endl;

    if (utilidadNeta >= 0)
    {
        cout << " - Utilidad Neta        : $ " << utilidadNeta << " (GANANCIA)" << endl;
    }
    else
    {
        cout << " - Utilidad Neta        : $ " << utilidadNeta << " (PERDIDA)" << endl;
    }

    cout << "-----------------------------------------------------------------------------\n"
         << endl;
}

// MÉTODOS NUMÉRICOS

// Método Regula Falsi, calcula el punto de equilibrio entre ventas y gastos.
vector<double> MetRegulaFalsi(const FinanzasBase &finanzas)
{
    // 1. Calculamos los totales directamente desde la estructura limpia
    double totalGF = 0;
    for (size_t i = 0; i < finanzas.gastosFijos.size(); i++)
    {
        totalGF += finanzas.gastosFijos[i].monto;
    }

    double costoVarUnd = 0;
    for (size_t i = 0; i < finanzas.gastosVariables.size(); i++)
    {
        costoVarUnd += finanzas.gastosVariables[i].monto;
    }

    double precioUnd = finanzas.precioUnd;

    vector<double> historialXr;

    // 2. Validación de viabilidad financiera (Margen de Contribución)
    if ((precioUnd - costoVarUnd) <= 0)
    {
        cout << "\n------------------------------- Regula Falsi --------------------------------" << endl;
        cout << "Punto de equilibrio incalculable..." << endl;
        cout << "ADVERTENCIA: El precio por unidad es menor o igual al costo variable unitario." << endl;
        return historialXr;
    }

    // 3. Variables de tu algoritmo
    double a = 0;
    double b = (totalGF == 0) ? 100 : totalGF * 2; // Rango inicial de búsqueda
    double xr = 0;
    double tolerancia = 0.0001;
    double error = 1.0;
    int iteracion = 1;

    historialXr.push_back(xr);

    // 4. Imprimir encabezado con fórmulas (Tu diseño original)
    cout << "\n------------------------------- Regula Falsi --------------------------------" << endl;
    cout << "ECUACION PLANTEADA" << endl;
    cout << "  f(x) = PreUnd * x - ( totalGF + CostoVarUnd * x) = 0" << endl;
    cout << "\nVARIABLES" << endl;
    cout << "  F(x)         : Funcion respecto a X" << endl;
    cout << "  x            : (Incognita - Unidades)" << endl;
    cout << "  PreUnd       : $ " << precioUnd << " (Precio por Unidad)" << endl;
    cout << "  totalGF      : $ " << totalGF << " (Gastos Fijos Totales)" << endl;
    cout << "  CostoVarUnd  : $ " << costoVarUnd << " (Costo Variable por Unidad)" << endl;
    cout << "\nFORMULAS" << endl;
    cout << "  xr    = (a*f(b) - b*f(a)) / (f(b) - f(a))" << endl;
    cout << "  f(a)  = PreUnd * a - ( totalGF + CostoVarUnd * a)" << endl;
    cout << "  f(b)  = PreUnd * b - ( totalGF + CostoVarUnd * b)" << endl;
    cout << "  f(xr) = PreUnd * xr - ( totalGF + CostoVarUnd * xr)" << endl;
    cout << "\nPROCEDIMIENTO" << endl;

    // 5. Bucle del método numérico
    while (error > tolerancia && iteracion <= 100)
    {
        double fa = precioUnd * a - (totalGF + costoVarUnd * a);
        double fb_val = precioUnd * b - (totalGF + costoVarUnd * b);

        // Protección contra división entre cero
        if ((fb_val - fa) == 0)
            break;

        xr = (a * fb_val - b * fa) / (fb_val - fa);
        double fxr = precioUnd * xr - (totalGF + costoVarUnd * xr);
        error = fabs(fxr);

        if (fa * fxr < 0)
        {
            b = xr;
        }
        else
        {
            a = xr;
        }

        cout << "\n----- Iteracion " << iteracion << " -----" << endl;
        cout << "  a: " << a << endl;
        cout << "  f(a): " << fa << endl;
        cout << "  b: " << b << endl;
        cout << "  f(b): " << fb_val << endl;
        cout << "  xr: " << xr << endl;
        cout << "  f(xr): " << fxr << endl;
        cout << "  Error: " << error << endl;

        historialXr.push_back(xr);
        iteracion++;
    }

    cout << "\n-----------------------------------------------------------------------------" << endl;
    cout << " El Punto de Equilibrio exacto es: " << xr << " Unidades Vendidas." << endl;
    cout << " (Se sugiere vender al menos " << ceil(xr) << " unidades para evitar perdidas)." << endl;
    cout << "-----------------------------------------------------------------------------" << endl;

    return historialXr;
}

// Método Runge Kutta 4to Orden, calcula la variación del capital en cierto período de tiempo.
vector<double> MetRK4(const FinanzasBase &finanzas, int meses, double tasaCrecimientoPct)
{
    // 1. Calculamos los Ingresos y Gastos desde la estructura
    double totalGF = 0;
    for (size_t i = 0; i < finanzas.gastosFijos.size(); i++)
    {
        totalGF += finanzas.gastosFijos[i].monto;
    }

    double totalGV = 0;
    for (size_t i = 0; i < finanzas.gastosVariables.size(); i++)
    {
        totalGV += finanzas.gastosVariables[i].monto;
    }

    double ingresosMensuales = finanzas.precioUnd * finanzas.cantidadUnidades;
    double gastoT = totalGF + (totalGV * finanzas.cantidadUnidades);
    double utilidadNeta = ingresosMensuales - gastoT;

    // 2. Variables de tu metodo
    double r = tasaCrecimientoPct / 100.0; // Convertir % a decimales
    double x = 0;                          // Periodo inicial (Mes 0)
    double y = finanzas.capitalInicial;    // Capital inicial
    double h = 1.0;                        // Paso de integracion = 1 mes

    vector<double> Capitales;
    Capitales.push_back(y);

    // 3. Encabezado explicativo (Tu diseño original)
    cout << "\n--------------------------- Runge-Kutta 4to Orden ---------------------------" << endl;
    cout << "ECUACION PLANTEADA" << endl;
    cout << "  dC/dt = UtilidadNeta + (r * C)" << endl;
    cout << "\nVARIABLES" << endl;
    cout << "  dC/dt        : Variacion del Capital respecto al Tiempo" << endl;
    cout << "  UtilidadNeta : $ " << utilidadNeta << " (Ingresos - Gastos Totales)" << endl;
    cout << "  r            : " << r << " (Tasa de Crecimiento/Rendimiento Decimal)" << endl;
    cout << "  C (Inicial)  : $ " << y << " (Capital Inicial)" << endl;
    cout << "  h            : " << h << " (Marca de paso = 1 mes)" << endl;
    cout << "\nFORMULAS" << endl;
    cout << "  k1   = h * f(xn, yn)" << endl;
    cout << "  k2   = h * f(xn + h/2, yn + k1/2)" << endl;
    cout << "  k3   = h * f(xn + h/2, yn + k2/2)" << endl;
    cout << "  k4   = h * f(xn + h,   yn + k3)" << endl;
    cout << "  yn+1 = yn + (1/6) * (k1 + 2k2 + 2k3 + k4)" << endl;
    cout << "\nPROCEDIMIENTO" << endl;
    cout << "Mes " << x << ": $ " << y << endl;

    // 4. Bucle del algoritmo
    for (int i = 0; i < meses; i++)
    {
        double k1 = h * (utilidadNeta + (r * y));
        double k2 = h * (utilidadNeta + (r * (y + k1 / 2.0)));
        double k3 = h * (utilidadNeta + (r * (y + k2 / 2.0)));
        double k4 = h * (utilidadNeta + (r * (y + k3)));

        y = y + (1.0 / 6.0) * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
        x = x + h;

        cout << "\nMes " << x << ":" << endl;
        cout << "  k1: " << k1 << endl;
        cout << "  k2: " << k2 << endl;
        cout << "  k3: " << k3 << endl;
        cout << "  k4: " << k4 << endl;
        cout << "  Capital: $ " << y << endl;

        Capitales.push_back(y); // Guarda el capital de este mes
    }

    cout << "\n-----------------------------------------------------------------------------" << endl;
    cout << "Resultado Final (Mes " << meses << "): $ " << y << endl;
    cout << "-----------------------------------------------------------------------------\n"
         << endl;

    return Capitales;
}

// Función utilizada para recolectar el historial de meses de estudio, se aplica en el método de mínimos cuadrados.
void LlenarHistorial(vector<double> &mesesHistoricos, vector<double> &ingresosHistoricos)
{
    cout << "\n----------------------- Insercion de Datos Historicos -----------------------" << endl;
    int numMeses = RellenarInt("Ingrese la cantidad de meses a estudiar (2-60): ", 2, 60);
    mesesHistoricos.reserve(numMeses);
    ingresosHistoricos.reserve(numMeses);

    for (int i = 0; i < numMeses; ++i)
    {
        double mes = RellenarDouble(" Ingrese el mes de estudio: ", 1, 60);
        double ingreso = RellenarDouble(" Inserte los ingresos obtenidos en el mes: $ ", 1, 1000000);
        mesesHistoricos.push_back(mes);
        ingresosHistoricos.push_back(ingreso);
    }
}

// Método de mínimos cuadrados, estima el rendimiento futuro del negocio.
vector<double> MetMinimosCuadrados(const vector<double> &x, const vector<double> &y, int mesesAProyectar)
{
    int n = x.size();
    vector<double> tendecias;
    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;

    cout << "\n-------------------- Regresion Lineal (Minimos Cuadrados) -------------------" << endl;
    cout << "\nTABLA DE DATOS HISTORICOS Y SUMATORIAS" << endl;
    cout << "-----------------------------------------------------------------------------" << endl;
    cout << "  Mes (X)   |   Monto Historico (Y)   |        X^2        |       X * Y      " << endl;
    cout << "-----------------------------------------------------------------------------" << endl;

    for (int i = 0; i < n; i++)
    {
        double x2 = x[i] * x[i];
        double xy = x[i] * y[i];

        sumX += x[i];
        sumY += y[i];
        sumX2 += x2;
        sumXY += xy;

        cout << "  " << x[i] << "\t    |  $ " << y[i] << "\t\t   |  " << x2 << "\t       |  $ " << xy << endl;
    }

    cout << "\nSUMAS" << endl;
    cout << "  Sum(X)=" << sumX << " | Sum(Y)=" << sumY
         << " | Sum(X^2)=" << sumX2 << " | Sum(XY)=" << sumXY << endl;

    // Calculo de la pendiente (m) e interseccion (b)
    double denominador = (n * sumX2 - sumX * sumX);
    if (denominador == 0)
    {
        cout << "\nError matematico: Division entre cero al calcular la pendiente." << endl;
        return tendecias;
    }

    double m = (n * sumXY - sumX * sumY) / denominador;
    double b = (sumY - m * sumX) / n;

    cout << "\nFORMULAS PLANTEADAS" << endl;
    cout << "  m = [ n * Sum(XY) - Sum(X)*Sum(Y) ] / [ n * Sum(X^2) - (Sum(X))^2 ]" << endl;
    cout << "  b = [ Sum(Y) - m * Sum(X) ] / n" << endl;

    cout << "\nMODELO DE TENDENCIA OBTENIDO" << endl;
    cout << "  Pendiente (m)    : " << m << " (Variacion por mes)" << endl;
    cout << "  Interseccion (b) : " << b << " (Base estimada)" << endl;
    cout << "  Ecuacion Recta   : Y = (" << m << ") * X + (" << b << ")" << endl;

    if (m > 0)
    {
        cout << "  DIAGNOSTICO      : Tendencia POSITIVA (Crecimiento)." << endl;
    }
    else if (m < 0)
    {
        cout << "  DIAGNOSTICO      : Tendencia NEGATIVA (Caida de ingresos)." << endl;
    }
    else
    {
        cout << "  DIAGNOSTICO      : Tendencia NEUTRA (Ventas constantes)." << endl;
    }

    cout << "\nPROYECCION FUTURA CON LA RECTA:" << endl;
    double ultimoMes = x.back();

    for (int i = 1; i <= mesesAProyectar; i++)
    {
        double mesFuturo = ultimoMes + i;
        double valorProyectado = m * mesFuturo + b;

        if (valorProyectado < 0)
            valorProyectado = 0; // Control de piso financiero

        cout << "  Mes Proyectado " << mesFuturo << ": $ " << valorProyectado << endl;
        tendecias.push_back(valorProyectado);
    }

    cout << "-----------------------------------------------------------------------------\n"
         << endl;
    return tendecias;
}

// Método Gauss Siedel, calcula los posibles escenarios de retotno sobre la inversión.
vector<double> MetGaussSeidel(double utilidadNeta, double capitalInicial)
{

    double Rsi = (utilidadNeta / capitalInicial) * 100.0;

    double tolerancia = 0.0001;
    double error = 1.0;
    int iteracion = 1;

    // Matriz A y Vector B basados en tu logica de escenarios
    vector<vector<double>> A = {
        {1.0, 0.1, 0.0}, // x1 depende 100% de si, y un 10% de x2.
        {0.0, 1.0, 0.1}, // x2 depende 100% de si, y un 10% de x3.
        {0.0, 0.0, 1.0}  // X3 depende 100% de si.
    };

    // b1 Rsi pesimista 60%, b2 Rsi base, b3 Rsi optimista 150%
    vector<double> b = {Rsi * 0.6, Rsi, Rsi * 1.5};
    vector<double> x = {0.0, 0.0, 0.0};
    vector<double> resultados;

    cout << "\n-------------------------------- Gauss-Seidel -------------------------------" << endl;
    cout << "SISTEMA DE ECUACIONES LINEALES PLANTEADO" << endl;
    cout << "  A * x = b\n"
         << endl;
    cout << "\nVARIABLES" << endl;
    cout << "  A : Matriz de coeficientes (Relaciones de dependencia entre escenarios)" << endl;
    cout << "  x : Vector de incognitas (ROI estabilizado a calcular)" << endl;
    cout << "  b : Vector de terminos independientes (Valores iniciales del ROI)" << endl;
    cout << "  b1 (Pesimista 60%)  : " << fixed << setprecision(2) << b[0] << " %" << endl;
    cout << "  b2 (Base 100%)      : " << b[1] << " %" << endl;
    cout << "  b3 (Optimista 150%) : " << b[2] << " %" << endl;
    cout << "\nFORMULA" << endl;
    cout << "  xi = [ bi - Sumatoria(A[i][j]*x[j]) ] / A[i][i]" << endl;
    cout << "\nPROCEDIMIENTO" << endl;

    // Se agrega limite de 50 iteraciones por pura seguridad de software
    while (error > tolerancia && iteracion < 50)
    {
        vector<double> Xviejo = x;

        for (int i = 0; i < 3; i++)
        {
            double suma = b[i];
            for (int j = 0; j < 3; j++)
            {
                if (j != i)
                {
                    suma -= A[i][j] * x[j];
                }
            }
            x[i] = suma / A[i][i];
        }

        error = 0;
        for (int i = 0; i < 3; i++)
        {
            error = max(error, fabs(x[i] - Xviejo[i]));
        }

        cout << "\n----- Iteracion " << iteracion << " -----" << endl;
        cout << "  x1 (Pesimista) : " << x[0] << " %" << endl;
        cout << "  x2 (Base)      : " << x[1] << " %" << endl;
        cout << "  x3 (Optimista) : " << x[2] << " %" << endl;
        cout << "  Error Maximo   : " << fixed << setprecision(5) << error << endl; // Mas precision en el error

        iteracion++;
    }

    cout << "\n-----------------------------------------------------------------------------" << endl;
    cout << "RESULTADOS FINALES (Puntos de Estabilizacion de ROI):" << endl;
    cout << "  ROI Pesimista Estabilizado : " << fixed << setprecision(2) << x[0] << " %" << endl;
    cout << "  ROI Base Estabilizado      : " << x[1] << " %" << endl;
    cout << "  ROI Optimista Estabilizado : " << x[2] << " %" << endl;
    cout << "-----------------------------------------------------------------------------\n"
         << endl;

    resultados.push_back(x[0]);
    resultados.push_back(x[1]);
    resultados.push_back(x[2]);

    return resultados;
}

// EXPORTACIÓN DE DATOS

void ExportarJSON(string nomNegocio, string sector, string producto, double capInicial, double utilNeta, double puntoEquilibrioRF,
                  vector<double> capitalRK4, vector<double> proyeccionesFinancieras, vector<double> ResultadoGS)
{
    ofstream archivo("Reporte_Rentabilidad.json");

    auto vecJson = [&](string nombre, vector<double> v, bool ultima = false)
    {
        archivo << "    \"" << nombre << "\": [";
        for (int i = 0; i < v.size(); i++)
            archivo << v[i] << (i < (int)v.size() - 1 ? ", " : "");
        archivo << "]" << (ultima ? "\n" : ",\n");
    };

    archivo << "{\n";

    // Datos del Negocio.
    archivo << "  \"datos_negocio\": {\n";
    archivo << "    \"nombre\": \"" << nomNegocio << "\",\n";
    archivo << "    \"sector\": \"" << sector << "\",\n";
    archivo << "    \"producto\": \"" << producto << "\",\n";
    archivo << "    \"capital_inicial\": " << capInicial << ",\n";
    archivo << "    \"utilidad_neta\": " << utilNeta << "\n";
    archivo << "  },\n";

    // Modulo 1: Punto de Equilibrio.
    archivo << "  \"punto_equilibrio\": {\n";
    archivo << "    \"metodo\": \"Regula Falsi\",\n";
    archivo << "    \"unidades_exactas\": " << puntoEquilibrioRF << "\n";
    archivo << "  },\n";

    // Modulo 2: Evolucion del Capital..
    archivo << "  \"evolucion_capital\": {\n";
    archivo << "    \"metodo\": \"Runge-Kutta 4to Orden\",\n";
    vecJson("proyeccion_mensual", capitalRK4, true); // true para cerrar el bloque sin coma
    archivo << "  },\n";

    // Modulo 3: Tendencias Financieras.
    archivo << "  \"tendencias_futuras\": {\n";
    archivo << "    \"metodo\": \"Regresion Lineal (Minimos Cuadrados)\",\n";
    vecJson("ingresos_proyectados", proyeccionesFinancieras, true);
    archivo << "  },\n";

    // Modulo 4: Escenarios de Riesgo.
    archivo << "  \"escenarios_roi\": {\n";
    archivo << "    \"metodo\": \"Gauss-Seidel\",\n";
    archivo << "    \"pesimista_estabilizado\": " << ResultadoGS[0] << ",\n";
    archivo << "    \"base_estabilizado\": " << ResultadoGS[1] << ",\n";
    archivo << "    \"optimista_estabilizado\": " << ResultadoGS[2] << "\n";
    archivo << "  }\n";

    archivo << "}\n";
    archivo.close();

    cout << "  Archivo 'Reporte_Rentabilidad.json' exportado correctamente..." << endl;
}

// FUNCIÓN PRINCIPAL

int main()
{
    cout << "\n==================== SISTEMA DE RENTABILIDAD DE NEGOCIOS 2.0 ====================" << endl;

    cout << fixed << setprecision(2); // Fija 2 decimales.

    // Se aplican las funciones.
    IdentidadNegocio identidad = RellenarIdentidadNegocio();
    FinanzasBase finanzas = RellenarFinanzasBase();

    MostrarDashboard(identidad, finanzas);

    // Vectores para la función LLenarHistorial
    vector<double> mesesHistoricos;
    vector<double> ingresosHistoricos;
    bool historialLleno = false; // Nos avisa si ya el usuario metio los datos

    // Vectores de los métodos, después son exportados en el Json.
    vector<double> puntoEquilibrio;
    vector<double> evolucionCapitalRK4;
    vector<double> tendeciasMC;
    vector<double> roi;

    int opc = 0;
    do
    {
        // Ménu principal a mostrar.
        cout << "\n-----------------------------------------------------------------------------" << endl;
        cout << "|                          MENU PRINCIPAL                                   |" << endl;
        cout << "-----------------------------------------------------------------------------" << endl;
        cout << "| 1. Punto de Equilibrio                                                    |" << endl;
        cout << "| 2. Evolucion del Capital                                                  |" << endl;
        cout << "| 3. Tendencias Financieras                                                 |" << endl;
        cout << "| 4. Analisis de Escenarios de Riesgo                                       |" << endl;
        cout << "| 5. Salir y Exportar Resultados a JSON                                     |" << endl;
        cout << "-----------------------------------------------------------------------------" << endl;

        opc = RellenarInt("\nSeleccione una opcion del menu (1-5): ", 1, 5);

        // Switch que muestra cada una de las opciones.
        switch (opc)
        {
        case 1:
        {
            cout << "\n---------------------------- PUNTO DE EQUILIBRIO ----------------------------" << endl;

            puntoEquilibrio = MetRegulaFalsi(finanzas);

            break;
        }

        case 2:
        {
            cout << "\n-------------------------- EVOLUCION DEL CAPITAL ----------------------------" << endl;

            cout << "\n---------------------------- Insercion de Datos -----------------------------" << endl;
            int meses = RellenarInt("Ingrese la cantidad de meses a proyectar (1-60): ", 1, 60);
            double tasaPct = RellenarDouble("Ingrese el procentaje de la tasa mensual: ", 0.0, 100.0);

            evolucionCapitalRK4 = MetRK4(finanzas, meses, tasaPct);

            break;
        }

        case 3:
        {
            cout << "\n-------------------------- TENDENCIAS FINANCIERAS ---------------------------" << endl;

            mesesHistoricos.clear();
            ingresosHistoricos.clear();

            LlenarHistorial(mesesHistoricos, ingresosHistoricos);

            int mesesFuturos = RellenarInt("Ingrese la cantidad de meses a futuro a proyectar (1-24): ", 1, 24);

            tendeciasMC = MetMinimosCuadrados(mesesHistoricos, ingresosHistoricos, mesesFuturos);

            break;
        }

        case 4:
        {
            cout << "\n---------------------- ANALISIS DE ESCENARIOS DE RIESGO ---------------------" << endl;

            roi = MetGaussSeidel(finanzas.precioUnd * finanzas.cantidadUnidades - (finanzas.gastosFijos.size() + finanzas.gastosVariables.size()),
                                 finanzas.capitalInicial);

            break;
        }

        case 5:
        {

            cout << "\nSaliendo del programa..." << endl;

            ExportarJSON(identidad.nombre, identidad.sector, identidad.servicio, finanzas.capitalInicial,
                         finanzas.precioUnd * finanzas.cantidadUnidades - (finanzas.gastosFijos.size() + finanzas.gastosVariables.size()),
                         puntoEquilibrio.empty() ? 0.0 : puntoEquilibrio.back(), evolucionCapitalRK4, tendeciasMC, roi);

            break;
        }

        default:
        {
            break;
        }
        }

    } while (opc != 5);

    cout << "=================================================================================\n"
         << endl;

    return 0;
}
