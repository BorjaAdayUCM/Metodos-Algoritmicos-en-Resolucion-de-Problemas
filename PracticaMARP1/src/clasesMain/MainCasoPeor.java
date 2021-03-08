package clasesMain;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

import arbolAutoajustable.ArbolAutoajustable;

public class MainCasoPeor {

	private static ArbolAutoajustable arbol = null;

	public static void main(String[] args) throws IOException {
		
		
		FileWriter fichero = new FileWriter("insertar.txt");;
        PrintWriter pw = new PrintWriter(fichero);
        
        FileWriter fichero1 = new FileWriter("borrar.txt");;
        PrintWriter pw1 = new PrintWriter(fichero1);
        
        FileWriter fichero2 = new FileWriter("buscar.txt");;
        PrintWriter pw2 = new PrintWriter(fichero2);
		
		long timeTotal = 0, timeParcial = 0, startTime = 0;
		for(int i = 0; i <= 30000; i += 1000) {
			for(int j = 0; j < 50; j++) {
				for(int k = 0; k < 1000; k++) {
					arbol = crearArbol(i);
					startTime = System.nanoTime();
					arbol.insertar(-1);
					timeParcial += (System.nanoTime() - startTime);
				}
				timeTotal += (timeParcial / 1000);
				timeParcial = 0;
			}
			System.out.println(arbol.getNumNodos());
			pw.println(arbol.getNumNodos() + " " + timeTotal / 50);
			timeTotal = 0;
		}
		
		timeTotal = 0; timeParcial = 0; startTime = 0;
		for(int i = 0; i <= 30000; i += 1000) {
			for(int j = 0; j < 50; j++) {
				for(int k = 0; k < 1000; k++) {
					arbol = crearArbol(i);
					startTime = System.nanoTime();
					arbol.borrar(0);
					timeParcial += (System.nanoTime() - startTime);
				}
				timeTotal += (timeParcial / 1000);
				timeParcial = 0;
			}
			System.out.println(arbol.getNumNodos());
			pw1.println(arbol.getNumNodos() + " " + timeTotal / 50);
			timeTotal = 0;
		}
		
		timeTotal = 0; timeParcial = 0; startTime = 0;
		for(int i = 0; i <= 30000; i += 1000) {
			for(int j = 0; j < 50; j++) {
				for(int k = 0; k < 1000; k++) {
					arbol = crearArbol(i);
					startTime = System.nanoTime();
					arbol.buscar(0);
					timeParcial += (System.nanoTime() - startTime);
				}
				timeTotal += (timeParcial / 1000);
				timeParcial = 0;
			}
			System.out.println(arbol.getNumNodos());
			pw2.println(arbol.getNumNodos() + " " + timeTotal / 50);
			timeTotal = 0;
		}
		
		pw.close();
		pw1.close();
		pw2.close();
		
	}
	
	private static ArbolAutoajustable crearArbol(int numElementos) {
		ArbolAutoajustable arbol = new ArbolAutoajustable();
		for(int i = 0; i < numElementos; i++) {
			arbol.insertar(i);
		}
		return arbol;
	}
	
}
