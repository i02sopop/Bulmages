#######
#Plugins
#######
#README.es
#20080501

Nombre: Demostración del funcionamiento de los plugins

Biblioteca: libpluginbt_example.so

Descripción: <H1>Ejemplo</H1>
<P>Sirve para demostrar el funcionamiento de los plugins.<br><br>Es, principalmente
un ejemplo de programacion.</P>
<B>Author:</B>Daniel Ripoll (dripoll.public@gmail.com)<BR>
<HR>

ParmBD: 

ArchivoSQLpatch: 

ArchivoSQLdeins: 

Dependencias:

Incompatibles:

Categorias: Utilidades avanzadas;

Orden: 90

Comentarios: 

Compilacion
===========

El plugin se compilará con el resto de bulmages y  se ubicara en bulmages/installbulmages/plugins/plugins con el nombre libpluginbt_example.so



Instalacion
===========

Configure la directiva CONF_PLUGINS_BULMATPV para que contenga la llamada a este plugin. Dicha directiva
puede ser a modo global en el archivo /etc/bulmages.conf o personalizada con los archivos /etc/bulmatpv_<<database>>.conf

Copie todos los archivos *.qm al directorio /usr/share/bulmages/traducciones .


