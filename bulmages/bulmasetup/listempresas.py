# -*- coding: utf-8 -*-

import sys
import os
from PyQt4.QtGui import *
from PyQt4.QtCore import *
from listempresasbase import *
from modificarfacturacion import ModificarFacturacion
from modificarcontabilidad import ModificarContabilidad


class ListEmpresas(QtGui.QDialog, Ui_ListEmpresasBase):
    def __init__(self, parent = None):
        QtGui.QDialog.__init__(self,parent)
	self.setupUi(self)
	
	self.process = QtCore.QProcess()
	self.connect(self.process, SIGNAL("readyReadStandardError()"), self.readErrors)
	self.connect(self.process, SIGNAL("finished()"), self.finished)
	self.connect(self.process, SIGNAL("started()"), self.started)
	
	self.show()
	self.buscarEmpresas()

	self.mui_listado.resizeColumnsToContents()
	self.mui_checkbox.setCheckState(Qt.Unchecked)
	
    def readOutput(self):
	self.mui_textBrowser.append(QString(self.process.readAllStandardOutput()))

    def readErrors(self):
	self.mui_textBrowser.append("<font color =\"#FF0000\">error: " + QString(self.process.readAllStandardError()) + "</font>")

    def finished(self):
	self.mui_textBrowser.append("<font color =\"#00FF00\">Done.</font>")

    def started(self):
	self.mui_textBrowser.append("<font color =\"#00FF00\">Start.</font>")

    def writecommand(self, comm):
	self.mui_textBrowser.append("<font color =\"#0000FF\">"+comm+"</font>")

    def guardaQuery(self, query):
	self.query = query
	self.fileHandle = open ( '/tmp/query.sql', 'w' )
	self.fileHandle.write ( query )
	self.fileHandle.close()

    def execQuery(self, query):
	self.writecommand(QString("----"))
	self.subcomand = query
	self.guardaQuery(self.subcomand)
	self.command = 'su postgres -c \"psql -t -f /tmp/query.sql ' + self.arrdatabase[self.i] + '\"'
	self.writecommand(self.command)
	self.process.start(self.command)
	self.process.waitForFinished(-1)
	return QString(self.process.readAllStandardOutput())

    def buscarEmpresas(self):
	self.mui_textBrowser.append("hola mundo")
	self.command = 'su - postgres -c \"echo \'SELECT datname FROM pg_database\' | psql -t template1\"'
	self.writecommand(self.command)
	self.process.start(self.command)
	self.process.waitForFinished(-1)
	self.databases = QString(self.process.readAllStandardOutput())
	self.writecommand(self.databases)
	self.arrdatabase = self.databases.split(QString(" "))
	self.mui_listado.setRowCount(self.arrdatabase.count() -1)
	self.i = 1
	self.progress = QtGui.QProgressBar(self)
#	self.progress.setGeometry(self.width /2, self.height/2, 200, 20)
	self.progress.setGeometry(self.width() / 2 -100, self.height() /2 -10, 200, 40)
	self.progress.setRange(0, self.arrdatabase.count())
	self.progress.show()
	while (self.i < self.arrdatabase.count()):
		self.writecommand(self.arrdatabase[self.i])
		self.mui_listado.setItem(self.i-1 , 1 , QTableWidgetItem(self.arrdatabase[self.i].replace('\n', '')))
		self.nombre = self.execQuery('SELECT valor FROM configuracion where nombre =\'NombreEmpresa\';').replace('\n', '')
		self.tipo = self.execQuery('SELECT valor FROM configuracion where nombre =\'Tipo\';').replace('\n', '').replace(' ','')
		self.databaserevision = self.execQuery('SELECT valor FROM configuracion where nombre =\'DatabaseRevision\';').replace('\n', '')
		self.mui_listado.setItem(self.i-1 , 0 , QTableWidgetItem(self.nombre))
		self.mui_listado.setItem(self.i-1 , 2 , QTableWidgetItem(self.tipo))
		self.mui_listado.setItem(self.i-1 , 3 , QTableWidgetItem(self.databaserevision))
		if (self.tipo == ''):
			self.mui_listado.hideRow(self.i-1)
		self.i = self.i + 1
		self.progress.setValue(self.progress.value() + 1)
	self.progress.hide()

    def on_mui_listado_cellDoubleClicked(self, row, col):
	self.mui_textBrowser.append(QString("<font color =\"#0000FF\">DOBLECLICK ")+QString.number(row)+QString("</font>"))
	if (self.mui_listado.item(row,2).text() == QString('BulmaFact')):
		self.fact = ModificarFacturacion(self.mui_listado.item(row,1).text())
		self.fact.exec_()
	if (self.mui_listado.item(row,2).text() == QString('BulmaCont')):
		self.cont = ModificarContabilidad(self.mui_listado.item(row,1).text())
		self.cont.exec_()

def main(args):
    app=QtGui.QApplication(args)
    win=ListEmpresas()
    win.exec_()
    sys.exit(app.exec_())

if __name__=="__main__":
    main(sys.argv)