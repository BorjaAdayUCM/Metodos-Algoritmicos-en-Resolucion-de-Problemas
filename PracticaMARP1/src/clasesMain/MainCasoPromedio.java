package clasesMain;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Random;

import arbolAutoajustable.ArbolAutoajustable;

public class MainCasoPromedio {
	
	private static ArbolAutoajustable arbol = null;
	private static Random rand = new Random();
	private static ArrayList<Integer> list = new ArrayList<Integer>();

	public static void main(String[] args) throws IOException {
		
		FileWriter fichero = new FileWriter("insertar.txt");;
        PrintWriter pw = new PrintWriter(fichero);
        
        FileWriter fichero1 = new FileWriter("borrar.txt");;
        PrintWriter pw1 = new PrintWriter(fichero1);
        
        FileWriter fichero2 = new FileWriter("buscar.txt");;
        PrintWriter pw2 = new PrintWriter(fichero2);
		
		long timeTotal = 0, timeParcial = 0, startTime = 0;
		for(int i = 0; i <= 200000; i += 1000) {
			arbol = crearArbol(i);
			for(int j = 0; j < 50; j++) {
				for(int k = 0; k < 1000; k++) {
					int numInsertar = rand.nextInt();
					while(list.contains(numInsertar)) numInsertar = rand.nextInt();
					startTime = System.nanoTime();
					arbol.insertar(numInsertar);
					timeParcial += (System.nanoTime() - startTime);
					list.remove((Integer)arbol.getValorRaiz());
					arbol.borrar(arbol.getValorRaiz());
				}
				timeTotal += (timeParcial / 1000);
				timeParcial = 0;
			}
			System.out.println(arbol.getNumNodos());
			pw.println(arbol.getNumNodos() + " " + timeTotal / 50);
			timeTotal = 0;
		}
		
		timeTotal = 0; timeParcial = 0; startTime = 0;
		for(int i = 0; i <= 200000; i += 1000) {
			arbol = crearArbol(i);
			for(int j = 0; j < 50; j++) {
				for(int k = 0; k < 1000; k++) {
					int numBorrar = (list.size() == 0 ? 0 : list.get(rand.nextInt(list.size())));
					startTime = System.nanoTime();
					arbol.borrar(numBorrar);
					timeParcial += (System.nanoTime() - startTime);
					arbol.insertar(numBorrar);
				}
				timeTotal += (timeParcial / 1000);
				timeParcial = 0;
			}
			System.out.println(arbol.getNumNodos());
			pw1.println(arbol.getNumNodos() + " " + timeTotal / 50);
			timeTotal = 0;
		}
		
		timeTotal = 0; timeParcial = 0; startTime = 0;
		for(int i = 0; i <= 200000; i += 1000) {
			arbol = crearArbol(i);
			for(int j = 0; j < 50; j++) {
				for(int k = 0; k < 1000; k++) {
					int numBuscar = (list.size() == 0 ? 0 : list.get(rand.nextInt(list.size())));
					startTime = System.nanoTime();
					arbol.buscar(numBuscar);
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
		list.clear();
		for(int i = 0; i < numElementos; i++) {
			int numInsertar = rand.nextInt();
			while(list.contains(numInsertar)) numInsertar = rand.nextInt();
			list.add(numInsertar);
			arbol.insertar(numInsertar);
		}
		return arbol;
	}

}
