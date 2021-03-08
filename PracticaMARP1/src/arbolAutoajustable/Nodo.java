package arbolAutoajustable;
// TODO: Auto-generated Javadoc
/**
 * Clase Nodo.
 */
public class Nodo {
	
	//*********//
	//Atributos//
	//*********//
	
	private int valor;
	private Nodo hijoDer;
	private Nodo hijoIzq;
	
	//*************//
	//Constructoras//
	//*************//
	
	/**
	 * Instancia un nuevo nodo.
	 *
	 * @param valor - valor con el que se desea crear el nodo.
	 */
	public Nodo(int valor) {
		this.valor = valor;
		this.hijoIzq = null;
		this.hijoDer = null;
	}
	
	//Funciones sobre un nodo.
	
	/**
	 * Devuelve si un nodo es hoja, es decir, si no tiene hijos.
	 *
	 * @return Devuelve true en caso de que el nodo sea hoja.
	 */
	public boolean esHoja() {
		return this != null && this.hijoIzq == null && this.hijoDer == null;
	}
	
	//*****************//
	//Getters y Setters//
	//*****************//
	public int getValor() {
		return valor;
	}

	public void setValor(int valor) {
		this.valor = valor;
	}

	public Nodo getHijoDer() {
		return hijoDer;
	}

	public void setHijoDer(Nodo hijoDer) {
		this.hijoDer = hijoDer;
	}

	public Nodo getHijoIzq() {
		return hijoIzq;
	}

	public void setHijoIzq(Nodo hijoIzq) {
		this.hijoIzq = hijoIzq;
	}

	@Override
	public String toString() {
		return "Nodo [valor=" + valor + "]";
	}
	
}
