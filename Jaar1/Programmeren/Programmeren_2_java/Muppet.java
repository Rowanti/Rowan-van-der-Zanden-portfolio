class Muppet{
    private String naam;
    private int leeftijd;
    private Muppet next;
    public Muppet(String naam, int leeftijd){
        setNaam(naam);
        setLeeftijd(leeftijd);
    }
    public void setNaam(String naam){
        this.naam = naam;
    }
    public void setLeeftijd(int leeftijd){
        this.leeftijd = leeftijd;
    }
    public String getNaam(){
        return this.naam;
    }
    public int getLeeftijd(){
        return this.leeftijd;
    }
    public void setNext(Muppet next){
        this.next = next;
    }
    public Muppet getNext(){
        return this.next;
    }
    public void print(){
        System.out.println("naam: " + this.naam + " ," + " leeftijd: " + this.leeftijd);
    }
}