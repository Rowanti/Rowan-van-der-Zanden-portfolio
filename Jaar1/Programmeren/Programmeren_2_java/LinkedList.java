class LinkedList {
    private int size;
    private Muppet start;
    /**
     * Een Element in de LinkedList pushen, 
     * als eerste checken of het element niet al in de linkedlist bestaat, daarna checken of de locatie van het pushen kleiner of gelijk is aan 0.
     * Als dit zo is, zal dit Element op locatie 0 worden gezet. Daarna word gecheckt of de positie van pushen groter is dat de grootte van de linkedlist.
     * Als dit zo is, zal dit Element aan het einde van de linkedlist worden gepushed.
     * Als het element midden in de linkedlist wordt gepushed zal de next pointen van de previous gekoppeld worden aan dit element,
     *  het element zal ook gekoppeld worden aan het eerstvolgende element in de lijst.
     * de grootte van de linkedlist wordt vergroot met 1
     * @param m : de naam van de muppet die in de linkedlist wordt gepushed.
     * @param positie : de positie waarop het element in de linkedlist word gepushed.
     */
    public void push (Muppet m, int positie) {
        if(m == null || peek(m.getNaam()) != null){
            return;
        }
        if(this.size == 0 || positie <= 0){
            m.setNext(this.start);
            this.start = m;
            size++;
            return;
        }
        else if (positie > this.size){
            positie = this.size;
        }
        Muppet previous = null;
        Muppet temp = this.start;
        for(int index = 0;index < positie; index++){
            if(temp != null){
                previous = temp;
                temp = temp.getNext();
            }
            else {
                this.size = index;
                push(m, positie);
                return;
            }
        }
        previous.setNext(m);
        m.setNext(temp);
        this.size++;
    }
/**
 * Eerst checken of het element dat gevraagdt word binnen de linkedlist valt.
 * de previous en de next aan elkaa koppelen en vervolgens het element poppen.
 * @param positie : de positie waarvan gepopt wordt
 * @return: niet returnen wanneer er aan geen van de eisen voldaan is.
 */
    public Muppet pop(int positie){
        if(positie < size && positie >= 0){
            Muppet temp = this.start;
            Muppet previous = null;
            for(int index = 0; index < positie; index++){
                previous = temp;
                temp = temp.getNext();
            }
            previous.setNext(temp.getNext());
            size--;
        return temp;
        }
        return null;
    }
/**
 * De linkedlist doorzoeken of er een muppet is dat dezelfde naam heeft als de muppet die gepopt zou worden
 * als deze er is zal de previous gekoppeld worden aan de next en zal dit element gepopt worden.
 * @param s : de naam van de muppet die gepopt zou worden
 * @return : niets returnen wanneer aan geen van de eisen voldaan is.
 */
    public Muppet pop(String s){
        Muppet temp = this.start;
        Muppet previous = null;
        for(int index = 0; index < this.size; index++){
            if(temp.getNext().getNaam().equals(s)){
                previous = temp;
                temp = temp.getNext();
                index = this.size;
            }
            else{
                previous = temp;
                temp = temp.getNext();
            }
        }
        previous.setNext(temp.getNext());
        size--;
        return temp;
    }

    /**
     * de linkedlist doorzoeken op er een muppet is met dezelfde naam als de muppet die gezogt word.
     * Als dit zo is zal deze gereturned worden 
     * @param s : de string die gezocht wordt
     * @return : niets returnen wanneer er aan geen van de eisen voldaan word
     */
    public Muppet peek(String s){
        Muppet temp = this.start;
        for(int index = 1; index < this.size; index++){
            if(temp.getNext().getNaam().equals(s)){
                return temp;
            }
            else{
                temp = temp.getNext();
            }
        }
        return null;
    }
    /**
     * eerst checken of de gezochte plaats in de linkedlist bevind.
     * Als dit zo is zal deze gereturned worden 
     * @param n : de plaats die gezocht wordt
     * @return : niets returnen wanneer er aan geen van de eisen voldaan word
     */
    public Muppet peek(int n){
        if(n < size && n >= 0){
            Muppet temp = this.start;
            for(int index = 0; index <= n; index++){
                    temp = temp.getNext();
            }
            return temp;
        }
        return null;
    }
    /**
     * Checken of de linkedlist niet gelijk is aan null
     * als dit niet zo is de linkedList doorlopen en de inhoud printen.
     * anders zal er geprint worden dat de linkedlist leeg is.
     */
    public void print(){
        if (this.start != null) {
            Muppet temp = this.start;
            System.out.println("Naam: " + temp.getNaam() + ", Leeftijd: " + temp.getLeeftijd());
            while (temp.getNext() != null) {
                temp = temp.getNext();
                System.out.println("Naam: " + temp.getNaam() + ", Leeftijd: " + temp.getLeeftijd());
            }
            System.out.println("List size: " + this.size);
        } else {
            System.out.println("Lijst leeg.");
        }
    }
}