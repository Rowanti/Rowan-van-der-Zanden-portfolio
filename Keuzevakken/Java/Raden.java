
/**
 * Keuzenvak Java - Eindopdracht
 * Rowan van der Zanden (1027332)
 */

import javax.swing.*;

class Raden {
    private int getal;
    private int vorigGetal;
    private boolean geraden = false;
    private int kansen;

    public int raadGetal() {
        String tekst = JOptionPane.showInputDialog(null, "Probeer het getal te raden", " ", 3);
        this.getal = Integer.parseInt(tekst);
        return getal;
    }

    public int aantalKansen() {
        String tekst = JOptionPane.showInputDialog(null, "Hoeveel kansen wil je?", " ", 3);
        this.kansen = Integer.parseInt(tekst);
        return kansen;
    }

    public void raad() {
        RandomNummer a = new RandomNummer();
        a.upperboundSet();
        a.randomizer();
        kansen = aantalKansen();
        while (geraden != true && kansen > 0) {
            this.getal = raadGetal();
            if (this.getal == a.getGetal()) {
                System.out.println("Het getal is geraden!!");
                System.out.println("Het getal was: " + a.getGetal());
                this.geraden = true;
            } else if (this.getal > a.getUpperbound()) {
                System.out.println("Dit getal is groter dan de bovengrens, probeer opnieuw");
            } else if(this.getal == this.vorigGetal){
                System.out.println("Dit getal heb je al geprobeerd te raden");
            } else if (this.getal > a.getGetal()) {
                System.out.println("Het getal is kleiner dan: " + this.getal);
                kansen--;
                this.vorigGetal = this.getal;
            } else if (this.getal < a.getGetal()) {
                System.out.println("Het getal is groter dan: " + this.getal);
                kansen--;
                this.vorigGetal = this.getal;
            }
        }
        if (kansen <= 0) {
            System.out.println("Jammer, je hebt verloren");
            System.out.println("Het getal was: " + a.getGetal());
        }
    }
}