--
-- Modificación de campos y funciones de la BD para la adaptacion para el plugin de Trazabilidad
--
\echo "********* INICIADO FICHERO DE ESTRUCTURA DEL PLUGIN DE DATOS BASE *********"

\echo ":: Establecemos los mensajes minimos a avisos y otros parametros ... "
\echo -n ":: "
SET client_min_messages TO WARNING;
SET log_min_messages TO WARNING;
-- SET log_error_verbosity TO TERSE;
BEGIN;

--
-- Estas primeras funciones cambiaran los tipos de columnas que est� como flotantes a NUMERIC.
-- Se trata de un parche que se desea aplicar para almacenar los tipos monetarios
-- ya que actualmente se encuantran almacenados como 'doubles' y es preferible
-- que se almacenen como tipo 'numeric'.
-- Todas devuelven como valor numeico el nmero de filas influenciadas por el cambio
--
-- Función auxiliar para borrar funciones limpiamente
--
create or replace function drop_if_exists_table (text) returns INTEGER AS '
DECLARE
tbl_name ALIAS FOR $1;
BEGIN
IF (select count(*) from pg_tables where tablename=$1) THEN
 EXECUTE ''DROP TABLE '' || $1;
RETURN 1;
END IF;
RETURN 0;
END;
'
language 'plpgsql';


create or replace function drop_if_exists_proc (text,text) returns INTEGER AS '
DECLARE
proc_name ALIAS FOR $1;
proc_params ALIAS FOR $2;
BEGIN
IF (select count(*) from pg_proc where proname=$1) THEN
 EXECUTE ''DROP FUNCTION '' || $1 || ''(''||$2||'') CASCADE'';
RETURN 1;
END IF;
RETURN 0;
END;
'
language 'plpgsql';


CREATE OR REPLACE FUNCTION aux() RETURNS INTEGER AS $$
DECLARE
	bs RECORD;
	ds RECORD;
BEGIN

	SELECT INTO ds * FROM tipo_iva;
	IF NOT FOUND THEN
            INSERT INTO tipo_iva (desctipo_iva) VALUES ('Exento');
            INSERT INTO tipo_iva (desctipo_iva) VALUES ('Reducido');
            INSERT INTO tipo_iva (desctipo_iva) VALUES ('Normal');
	
	    SELECT INTO bs idtipo_iva FROM tipo_iva WHERE desctipo_iva='Exento';
            IF FOUND THEN
		INSERT INTO tasa_iva (idtipo_iva, porcentasa_iva, fechatasa_iva, porcentretasa_iva) VALUES (bs.idtipo_iva, 0, '01/01/1973', 0);
    	    END IF;

            SELECT INTO bs idtipo_iva FROM tipo_iva WHERE desctipo_iva='Reducido';
	    IF FOUND THEN
	        INSERT INTO tasa_iva (idtipo_iva, porcentasa_iva, fechatasa_iva, porcentretasa_iva) VALUES (bs.idtipo_iva, 7, '01/01/1973', 2);
	    END IF;

	    SELECT INTO bs idtipo_iva FROM tipo_iva WHERE desctipo_iva='Normal';
	    IF FOUND THEN
	        INSERT INTO tasa_iva (idtipo_iva, porcentasa_iva, fechatasa_iva, porcentretasa_iva) VALUES (bs.idtipo_iva, 16, '01/01/1973', 4);
 	    END IF;
        END IF;
	
	SELECT INTO ds * FROM almacen;
	IF NOT FOUND THEN
	    INSERT INTO almacen (codigoalmacen, nomalmacen) VALUES ('000', 'Principal');
	END IF;
	
	SELECT INTO ds * FROM familia;
	IF NOT FOUND THEN
	    INSERT INTO familia (codigofamilia, nombrefamilia) VALUES ('000', 'Varios');
	END IF;
	
	SELECT INTO ds * FROM tipo_articulo;
	IF NOT FOUND THEN
	    INSERT INTO tipo_articulo (codtipo_articulo, desctipo_articulo) VALUES ('000', 'Genericos');
	END IF;

	SELECT INTO ds * FROM articulo;
	IF NOT FOUND THEN
	
	END IF;
	
	SELECT INTO ds * FROM trabajador;
	IF NOT FOUND THEN
	    INSERT INTO trabajador (nomtrabajador) VALUES ('Sin Definir');
	END IF;
	
	SELECT INTO ds * FROM serie_factura;
	IF NOT FOUND THEN
	    INSERT INTO serie_factura (codigoserie_factura, descserie_factura) VALUES ('DD', 'Principal');
	    INSERT INTO serie_factura (codigoserie_factura, descserie_factura) VALUES ('REC', 'Rectificativa');
	END IF;
	
	SELECT INTO ds * FROM pais;
	IF NOT FOUND THEN
	    INSERT INTO pais (descpais, cod2pais, cod3pais) VALUES ('España','es','esp');
	    SELECT INTO bs idpais FROM pais WHERE cod2pais = 'es';
	    IF FOUND THEN
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Alava');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Albacete');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Alicante');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Almería');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Asturias');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Avila');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Badajoz');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Baleares');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Barcelona');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Burgos');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Cáceres');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Cádiz');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Cantabria');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Castellón');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Ceuta');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Ciudad Real');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Córdoba');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Coruña, La');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Cuenca');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Gerona');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Granada');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Guadalajara');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Guipuzcoa');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Huelva');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Huesca');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Jaen');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'León');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Lérida');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Lugo');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Madrid');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Málaga');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Melilla');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Murcia');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Navarra');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Orense');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Palencia');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Palmas (Las)');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Pontevedra');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Rioja (La)');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Salamanca');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'S.C.Tenerife');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Segovia');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Sevilla');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Soria');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Tarragona');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Teruel');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Toledo');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Valencia');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Valladolid');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Vizcaya');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Zamora');
		INSERT INTO provincia (idpais, provincia) VALUES (bs.idpais, 'Zaragoza');
	    END IF;
	END IF;
	
	RETURN 0;
END;
$$   LANGUAGE plpgsql;
SELECT aux();
DROP FUNCTION aux() CASCADE;
\echo "Agregamos los datos de inicializacion."





-- ==============================================================================

-- Agregamos nuevos parametros de configuracion.
--
CREATE OR REPLACE FUNCTION actualizarevision() RETURNS INTEGER AS '
DECLARE
	as RECORD;
BEGIN
	SELECT INTO as * FROM configuracion WHERE nombre=''DBRev-DatosBase'';
	IF FOUND THEN
		UPDATE CONFIGURACION SET valor=''0.11.1-001'' WHERE nombre=''DBRev-DatosBase'';
	ELSE
		INSERT INTO configuracion (nombre, valor) VALUES (''DBRev-DatosBase'', ''0.11.1-001'');
	END IF;
	RETURN 0;
END;
'   LANGUAGE plpgsql;
SELECT actualizarevision();
DROP FUNCTION actualizarevision() CASCADE;
\echo "Actualizada la revision de la base de datos a la version 0.11.1"


DROP FUNCTION drop_if_exists_table(text) CASCADE;
DROP FUNCTION drop_if_exists_proc(text,text) CASCADE;


COMMIT;