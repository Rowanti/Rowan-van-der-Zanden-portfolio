
/**
 * Keuzenvak Java - Eindopdracht
 * Rowan van der Zanden (1027332)
 */

import javax.swing.*;

public class Gokje {
    private static boolean doorgaan = true;

    public static void main(String[] args) {
        // blijft doorgaan met het spel zolang de speler dit wilt
        while (doorgaan == true) {
            Raden raad = new Raden();
            raad.raad();
            doorgaan();
        }
    }

    public static void doorgaan() {
        boolean input = false;
        String tekst;
        // om de inout van een user vragen net zolang tot er een valide input is gegeven
        while (input == false) {
            tekst = JOptionPane.showInputDialog(null, "Nog een keer? (ja/nee)", " ", 3);
            if (tekst.equals("ja")) {
                System.out.println("Het spel gaat door!");
                input = true;
            } else if (tekst.equals("nee")) {
                System.out.println("Het spel stopt");
                input = true;
                doorgaan = false;
            } else {
                System.out.println("geen valide input gegeven, probeer het opnieuw");
            }
        }
    }
}
