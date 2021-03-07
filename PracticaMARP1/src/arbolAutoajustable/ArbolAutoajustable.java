package arbolAutoajustable;
// TODO: Auto-generated Javadoc
/**
 * Clase ArbolAutoajustable.
 */
public class ArbolAutoajustable {
	
	//*********//
	//Atributos//
	//*********//	
	
	private Nodo raiz;

	//*************//
	//Constructoras//
	//*************//
	
	/**
	 * Instancia un nuevo arbol autoajustable.
	 */
	public ArbolAutoajustable() {
		this.raiz = null;
	}
	
	//****************//
	//Metodos privados//
	//****************//
	
	/**
	 * Comprueba que el arbol sea un arbol autoajustable.
	 *
	 * @param nodo - nodo actual desde el que comprueba que sea autoajustable.
	 * @return devuelve true en caso de que sea arbol autoajustable.
	 */
	private boolean esArbolAutoajustable(Nodo nodo) {
		//Si el nodo no existe es un subarbol autoajustable.
		if(nodo == null) return true;
		/*Si el nodo existe, debe comprobar que su hijoIzq sea estrictamente menor que el y el derecho estrictamente mayor que el
		  ademas de que sus hijos formen subarboles autoajustables*/
		return (nodo.getHijoIzq() == null || nodo.getHijoIzq().getValor() < nodo.getValor()) && 
			   (nodo.getHijoDer() == null || nodo.getHijoDer().getValor() > nodo.getValor()) && 
			   esArbolAutoajustable(nodo.getHijoIzq()) && esArbolAutoajustable(nodo.getHijoDer());
	}
	
	/**
	 * Obtiene la altura de un nodo.
	 *
	 * @param nodo - nodo del que se desea saber la altura.
	 * @return Devuelve la altura del nodo solicitado, -1 en caso de que el nodo no exista.
	 */
	private int getAltura(Nodo nodo) {
		//Si el nodo no existe devuelve -1
		if(nodo == null) return -1;
		//Si el nodo existe suma uno y pregunta a sus hijos.
		return Math.max(this.getAltura(nodo.getHijoIzq()), this.getAltura(nodo.getHijoDer())) + 1;
	}

	/**
	 * Devuelve el número de nodos del arbol que forma el nodo dado.
	 *
	 * @param nodo - nodo desde el que se desea saber la cantidad de descendientes.
	 * @return Devuelve el número de descendientes + 1 = numero de nodos que tiene el subarbol.
	 */
	private int getNumNodos(Nodo nodo) {
		//Si el nodo no existe devuelve 0
		if (nodo == null) return 0;
		//Si el nodo existe devuelve 1 y se llama recursivamente a izquierda y derecha.
		return this.getNumNodos(nodo.getHijoIzq()) + this.getNumNodos(nodo.getHijoDer()) + 1;
	}
	
	/**
	 * Realiza la rotacion a la izquierda desde el nodo dado.
	 *
	 * @param nodo - nodo origen desde el que se realiza la rotacion.
	 * @return Devuelve el nodo que ocupa el dado tras la rotacion.
	 */
	private Nodo rotacionIzq(Nodo nodo) {
		//Hijo derecho del nodo dado
		Nodo nodoAux = nodo.getHijoDer();
		//Cambio del hijo derecho del nodo dado por el hijo izquiero de su hijo derecho.
        nodo.setHijoDer(nodoAux.getHijoIzq());
        //El nodo dado pasa a ser el hijo izquierdo del hijo derecho del nodo dado.
        nodoAux.setHijoIzq(nodo);
        return nodoAux;
	}
	
	/**
	 * Realiza la rotacion a la derecha desde el nodo dado.
	 *
	 * @param nodo - nodo origen desde el que se realiza la rotación.
	 * @return Devuelve el nodo que ocupa el dado tras la rotacion.
	 */
	private Nodo rotacionDer(Nodo nodo) {
		//Hijo izquierdo del nodo dado
		Nodo nodoAux = nodo.getHijoIzq();
		//Cambio del hijo izquierdo del nodo dado por el hijo derecho de su hijo izquierdo.
		nodo.setHijoIzq(nodoAux.getHijoDer());
		//El nodo dado para a ser el hijo derecho del hijo izquierdo del nodo dado.
		nodoAux.setHijoDer(nodo);
		return nodoAux;
	}
	
	/**
	 * Realiza la rotacion a doble a la izquierda desde el nodo dado.
	 *
	 * @param nodo - nodo origen desde el que se realiza la rotación.
	 * @return Devuelve el nodo que ocupa el dado tras la rotacion.
	 */
	private Nodo rotacionDobleIzq(Nodo nodo) {
		Nodo hijoIzq = nodo.getHijoIzq();
		Nodo nietoIzq = nodo.getHijoIzq().getHijoIzq();
		nodo.setHijoIzq(hijoIzq.getHijoDer());
		hijoIzq.setHijoIzq(nietoIzq.getHijoDer());
		hijoIzq.setHijoDer(nodo);
		nietoIzq.setHijoDer(hijoIzq);
		return nietoIzq;
	}
	
	/**
	 * Realiza la rotacion doble a la derecha desde el nodo dado.
	 *
	 * @param nodo - nodo origen desde el que se realiza la rotación.
	 * @return Devuelve el nodo que ocupa el dado tras la rotacion.
	 */
	private Nodo rotacionDobleDer(Nodo nodo) {
		Nodo hijoDer = nodo.getHijoDer();
		Nodo nietoDer = nodo.getHijoDer().getHijoDer();
		nodo.setHijoDer(hijoDer.getHijoIzq());
		hijoDer.setHijoDer(nietoDer.getHijoIzq());
		hijoDer.setHijoIzq(nodo);
		nietoDer.setHijoIzq(hijoDer);
		return nietoDer;
	}

	/**
	 * Eleva a la raíz el nodo con la clave solicitada o el más cercano a la clave.
	 *
	 * @param clave - clave del nodo que se desea flotar.
	 * @param nodo - nodo origen desde el que se realiza la flotacion.
	 * @return Devuelve el nodo que pasa a ser la nueva raiz.
	 */
	private Nodo flotar(int clave, Nodo nodo) {
		//Si el nodo no existe se devuelve null.
		if(nodo == null) return null;
		//Si el nodo es el buscado se devuelve el nodo.
		else if(nodo.getValor() == clave) return nodo;
		else if(clave < nodo.getValor()) {
			//Si la clave es menor al nodo y no tiene hijo izquierdo se devuelve ese nodo pues es el más cercano.
			if(nodo.getHijoIzq() == null) return nodo;
			//Si el hijo izquierdo del nodo actual es el buscado rotamos a la derecha.
			else if(clave == nodo.getHijoIzq().getValor()) return rotacionDer(nodo);
			//Si el nieto izquierdo del nodo actual es el buscado hacemos una doble rotacion izquierda.
			else if(nodo.getHijoIzq().getHijoIzq() != null && clave == nodo.getHijoIzq().getHijoIzq().getValor()) return rotacionDobleIzq(nodo);
			//Si no se cumple ninguna anterior, volvemos a explorar la rama izquierda y rotamos a la derecha.
			nodo.setHijoIzq(this.flotar(clave, nodo.getHijoIzq()));
			return rotacionDer(nodo);
		}
		//Este caso es el mismo que el anterior pero en modo espejo.
		else {
			if(nodo.getHijoDer() == null) return nodo;
			else if(clave == nodo.getHijoDer().getValor()) return rotacionIzq(nodo);
			else if(nodo.getHijoDer().getHijoDer() != null && clave == nodo.getHijoDer().getHijoDer().getValor()) return rotacionDobleDer(nodo);
			nodo.setHijoDer(this.flotar(clave, nodo.getHijoDer()));
			return rotacionIzq(nodo);
		}
	}
	
	/**
	 * Inserta una nueva clave en el arbol.
	 *
	 * @param nuevoNodo - nodo que se quiere introducir en el arbol.
	 * @param nodo - nodo desde el que se busca la posicion para insertar el nuevo nodo.
	 */
	private void insertar(Nodo nuevoNodo, Nodo nodo) {
		//Si el valor ya existe, se sale del metodo.
		if(nuevoNodo.getValor() == nodo.getValor()) return;
		else if(nuevoNodo.getValor() < nodo.getValor()) {
			//Si el valor es menor al nodo actual y no tiene hijo izquierdo, se pone el valor como su hijo izquierdo.
			if(nodo.getHijoIzq() == null) nodo.setHijoIzq(nuevoNodo);
			//Si no se vuelve a llamar a insertar por la rama izquierda.
			this.insertar(nuevoNodo, nodo.getHijoIzq());
		}
		//Este else sigue la misma logica que el anterior pero en espejo.
		else {
			if(nodo.getHijoDer() == null) nodo.setHijoDer(nuevoNodo);
			this.insertar(nuevoNodo, nodo.getHijoDer());
		}
	}
	
	/**
	 * Imprime el subarbol que empieza con el nodo dado.
	 *
	 * @param nodo - nodo desde el que se quiere imprimir el arbol.
	 * @param altura - altura a la que se encuentra el nodo dado, siendo la raiz 0.
	 */
	private void imprimeArbol(Nodo nodo, int altura){ 
        if(nodo == null) return;
        imprimeArbol(nodo.getHijoDer(), altura + 1);
        if(altura != 0){ 
            for(int i = 0; i < altura - 1; i++)
                System.out.print("|\t");
                System.out.println("|-------(" + nodo.getValor() + ")");
            }
        else 
            System.out.println("(" + nodo.getValor() + ")");
        imprimeArbol(nodo.getHijoIzq(), altura + 1);
    }
	
	//****************//
	//Metodos publicos//
	//****************//
	
	/**
	 * Devuelve si el arbol esta vacio o no.
	 *
	 * @return Devuelve true en caso de que el arbol este vacio.
	 */
	public boolean esVacio() {
		return this.raiz == null;
	}
	
	/**
	 * Comprueba que sea un arbol autoajustable.
	 *
	 * @return Devuelve true en caso de que sea un arbol autoajustable.
	 */
	public boolean esArbolAutoajustable() {
		return esArbolAutoajustable(this.raiz);
	}
	
	/**
	 * Devuelve el valor de la raiz, util para calcular los costes para el mejor caso.
	 *
	 * @return Devuelve el valor del nodo raiz.
	 */
	public int getValorRaiz() {
		return this.raiz.getValor();
	}
	
	/**
	 * Devuelve la altura del arbol.
	 *
	 * @return Devuelve la altura del arbol.
	 */
	public int getAltura() {
		return this.getAltura(this.raiz);
	}
	
	/**
	 * Devuelve el numero de nodos del arbol.
	 *
	 * @return Devuelve el numero de nodos del arbol.
	 */
	public int getNumNodos() {
		return this.getNumNodos(this.raiz);
	}
	
	/**
	 * Insertar una nueva clave en el arbol.
	 *
	 * @param clave - clave que se desea insertar.
	 */
	public void insertar(int clave) {
		//Si el arbol es vacio, digo que la raiz es un nuevo nodo con esa clave.
		if(this.esVacio()) this.raiz = new Nodo(clave);
		else {
			//En caso de que no sea vacio, inserto esa clave en el arbol y floto ese valor para llevarlo a la raiz.
			this.insertar(new Nodo(clave), this.raiz);
			this.raiz = flotar(clave, this.raiz);
		}
	}
	
	/**
	 * Borra la clave dada del arbol.
	 *
	 * @param clave - clave que se desea borrar.
	 */
	public void borrar(int clave) {
		//Si el arbol es vacio la clave no existe y por tanto se sale del metodo.
		if(this.esVacio()) return;
		//Lo busco para llevarlo a la raiz, y si devuelve distinto de null es que el nodo buscado se encuentra en la raiz.
		if(this.buscar(clave) != null) {
			//En caso de que el nodo a borrar no tenga hijos se elimina la raiz.
			if(this.raiz.esHoja()) this.raiz = null;
			//En caso de que solo tenga un hijo, ese hijo pasa a ser la raiz del arbol.
			else if(this.raiz.getHijoIzq() == null || this.raiz.getHijoDer() == null) this.raiz = (this.raiz.getHijoIzq() == null ? this.raiz.getHijoDer() : this.raiz.getHijoIzq());
			else {
				//En caso de que tenga los dos hijos, la raiz para a ser el hijo derecho mas profundo de su hijo izquierdo.
				//Si su hijo izquierdo no tiene hijo derecho,
				if(this.raiz.getHijoIzq().getHijoDer() == null) {
					//El hijo derecho de la raiz pasa a ser el hijo derecho del hijo izquierdo de la raiz.
					this.raiz.getHijoIzq().setHijoDer(this.raiz.getHijoDer());
					//El hijo izquierdo de la raiz para a ser la nueva raiz.
					this.raiz = this.raiz.getHijoIzq();
				}
				else {
					//Calculamos primero el nodo que va a pasar a convertirse en la raiz del arbol.
					Nodo antUltimoHijoDer = this.raiz.getHijoIzq();
					Nodo ultimoHijoDer = this.raiz.getHijoIzq().getHijoDer();
					while(ultimoHijoDer.getHijoDer() != null) {
						antUltimoHijoDer = ultimoHijoDer;
						ultimoHijoDer = ultimoHijoDer.getHijoDer();
					}
					//Actualizamos punterors para seguir teniendo un arbol de busqueda binario.
					antUltimoHijoDer.setHijoDer(ultimoHijoDer.getHijoIzq());
					ultimoHijoDer.setHijoDer(this.raiz.getHijoDer());
					ultimoHijoDer.setHijoIzq(this.raiz.getHijoIzq());
					//Convertimos el hijo derecho mas profundo del hijo izquierdo de la raiz en la nueva raiz.
					this.raiz = ultimoHijoDer;
				}
			}
		}
	}
	
	/**
	 * Buscar la clave dada en el arbol.
	 *
	 * @param clave - clave que se desea buscar.
	 * @return Devuelve null en caso de no encontrar la clave o el nodo que la contiene en caso satisfactorio.
	 */
	public Nodo buscar(int clave){
		//Si es vacio devuelve null
		if(this.esVacio()) return null;
		//Flotamos el valor buscado para elevarlo a la raiz.
		this.raiz = this.flotar(clave, this.raiz);
		//Si no es el valor buscado devolvemos null, en caso de que lo sea devolvemos el nodo raiz (pues se encontrará en esa posicion).
		if(this.raiz == null || this.raiz.getValor() != clave) return null;
		else return this.raiz;
	}
	
	/**
	 * Imprime el arbol desde la raiz.
	 */
	public void imprimeArbol() {
		this.imprimeArbol(this.raiz, 0);
	}

}
