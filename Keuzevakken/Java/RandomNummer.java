
/**
 * Keuzenvak Java - Eindopdracht
 * Rowan van der Zanden (1027332)
 */

import javax.swing.*;
import java.util.Random;

class RandomNummer {
    private int upperbound;
    private int getal;
    public int upperboundSet() {
        String tekst = JOptionPane.showInputDialog(null, "Voer een bovengrens in", " ", 3);
        this.upperbound = Integer.parseInt(tekst);
        return upperbound;
    }

    public void randomizer() {
        // genereerd een random waarde van 0 tot het gekozen getal
        Random rand = new Random();
        this.getal = rand.nextInt(this.upperbound);
    }

    public int getGetal() {
        return getal;
    }

    public int getUpperbound() {
        return upperbound;
    }
}