/**
 * einopdracht programmeren 4
 * Rowan van der Zanden - 1027332
 */
import java.util.Set;
import java.util.LinkedHashSet;
public class Student <Nummer, Naam, Geslacht, Klas, Richting>{
    Nummer nummer;
    Naam naam;
    Geslacht geslacht;
    Klas klas;
    Richting richting;
    Set<Vak> behaaldVak = new LinkedHashSet<>();
    Set<Vak> onbehaaldVak = new LinkedHashSet<>(); 
    Student(Nummer nu, Naam na, Geslacht ge, Klas kl, Richting ri){
        nummer = nu;
        naam = na;
        geslacht = ge;
        klas = kl;
        richting = ri;
    }
    public void addBehaaldVak(Vak behaaldVak) {
        this.behaaldVak.add(behaaldVak);
    }
    public void addOnbehaaldVak(Vak onbehaaldVak) {
        this.onbehaaldVak.add(onbehaaldVak);
    }
    public boolean checkVak(Vak vak){
        return behaaldVak.contains(vak);
    }
    public boolean checkFail(Vak vak){
        return onbehaaldVak.contains(vak);
    }
    public void checkGehaald(){
        for(Vak v: behaaldVak){
            System.out.println(v.getModulecode());
        }
    }
    public int optelSom(Student student){
        int som = 0;
        for(Vak v: behaaldVak){
            som+=v.getCijfer();
        }
        for(Vak v: onbehaaldVak){
            som+=v.getCijfer();
        }
        return som;
    }
    public int getCijfer(Vak vak){
        int cijfer = 0;
        for(Vak v: behaaldVak){
            if(vak == v){
                cijfer = v.getCijfer();
            }
        }
        for(Vak v: onbehaaldVak){
            if(vak ==v){
                cijfer = v.getCijfer();
            }
        }
        return cijfer;
    }
}