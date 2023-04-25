/**
 * einopdracht programmeren 4
 * Rowan van der Zanden - 1027332
 */

import java.util.Set;
import java.util.HashSet;
import java.util.LinkedHashSet;
import java.util.Random;
import java.lang.Math;
public class Administratie {
    Set<Vak> vakkenJaar1 = new HashSet<>();
    Set<Vak> vakkenJaar2 = new HashSet<>();
    Set<Vak> vakkenJaar3 = new HashSet<>();
    Set<Vak> vakkenJaar4 = new HashSet<>();
    Set<Student> studenten = new LinkedHashSet<>();
    Vak vak;
    Student student;

    // aanmaken vakken
    public void createVak(String vakcode, int jaar){
        Random ran = new Random();
        int upperboundCijfer = 10;
        Vak vak = new Vak(vakcode, ran.nextInt(upperboundCijfer)+1, jaar);
        this.vak = vak;
        if (vak.getJaar() == 1 ){
            vakkenJaar1.add(vak);
        }
        else if (vak.getJaar() == 2 ){
            vakkenJaar2.add(vak);
        }
        else if (vak.getJaar() == 3 ){
            vakkenJaar3.add(vak);
        }
        else if (vak.getJaar() == 4 ){
            vakkenJaar4.add(vak);
        }
        vakHalen();
    }

    // kijken of de student het vak heeft gehaald en het in de goede LinkedSet zetten
    public void vakHalen(){
        if(vak.getCijfer() > 5.5){
            student.addBehaaldVak(vak);
        }
        else if(vak.getCijfer() >= 1){
            student.addOnbehaaldVak(vak);
        }
    }

    // aanroepen van functies die de informatie geven die de administratie wilt weten.
    public void administratie(){
        System.out.println("studenten die het vak: " + vak.getModulecode() + " hebben gehaald: ");
        for(Vak v: vakkenJaar1){
            if(v.getModulecode() == "LLC"){
                showVakGehaald(v);
            }
        }
        System.out.println("studenten die het vak: " + vak.getModulecode() + " niet hebben gehaald: ");
        for(Vak v: vakkenJaar1){
            if(v.getModulecode() == "LLC"){
                showVakNietBehaald(v);
            }
        }
        System.out.println(" ");
        showStudent(this.student);
        optelSom(this.student);
        gemCijfer(this.vak);
        standaardDeviatie();
    }

    // aanmaken van studenten en vakken die deze studenten volgen.
    public void createStudent(){
        // Set<Vak> v = new HashSet<>();
        Student s1 = new Student<>(1027333, "Rowan", 'M', "1F", "CMI");
        this.student = s1;
        studenten.add(s1);
        createVak("PRO1", 1);
        createVak("TES1", 1);
        createVak("LLC", 1);
        Student s2 = new Student<>(1027334, "Vrouw1", 'V', "1A", "CMI");
        studenten.add(s2);
        this.student = s2;
        createVak("PRO1", 1);
        createVak("TES1", 1);
        createVak("LLC", 1);
        Student s3 = new Student<>(1027335, "Vrouw2", 'V', "2B", "CMI");
        studenten.add(s3);
        this.student = s3;
        createVak("PRO2", 2);
        createVak("TES2", 2);
        createVak("PROJ2", 2);
        Student s4 = new Student<>(1027336, "Man1", 'M', "3C", "CMI");
        studenten.add(s4);
        this.student = s4;
        createVak("PRO3", 3);
        createVak("TES3", 3);
        createVak("PROJ3", 3);
        Student s5 = new Student<>(1027337, "Man2", 'M', "4G", "CMI");
        studenten.add(s5);
        this.student = s5;
        createVak("PRO4", 4);
        createVak("TES5", 4);
        createVak("PROJ4", 4);
    }
    public void showVakGehaald(Vak vak){
        for(Student s: studenten){
            if(s.checkVak(vak)){
                System.out.println(s.naam + " (" + vak.getCijfer() + ")");
            }
        }
    }
    public void showVakNietBehaald(Vak vak){
        for(Student s: studenten){
            if(s.checkFail(vak)){
                System.out.println(s.naam + " (" + vak.getCijfer() + ")");
            }
        }        
    }
    public void showStudent(Student student){
        System.out.println("vakken die student " + student.naam + " heeft gehaald: ");
        student.checkGehaald();
        System.out.println(" ");
    }
    public void optelSom(Student student){
        System.out.println("Totaalcijfer van student "+ student.naam + ": " + student.optelSom(student));
    }

    // het gemmiddelde cijfer berekenen van het aangegeven vak
    // door alle jaren heen zoeken wanneer dit vak gegeven word.
    public void gemCijfer(Vak vak){
        float totaalcijfer = 0;
        float count = 0;
        String vakCode = vak.getModulecode();
        for (Vak v : vakkenJaar1) {
            if(v.getModulecode() == vakCode){
                count++;
                for(Student student: studenten){
                    totaalcijfer += student.getCijfer(v);
                }
            }
        }
        for (Vak v : vakkenJaar2) {
            if(v.getModulecode() == vakCode){
                count++;
                for(Student student: studenten){
                    totaalcijfer += student.getCijfer(v);
                }
            }
        }
        for (Vak v : vakkenJaar3) {
            if(v.getModulecode() == vakCode){
                count++;
                for(Student student: studenten){
                    totaalcijfer += student.getCijfer(v);
                }
            }
        }
        for (Vak v : vakkenJaar4) {
            if(v.getModulecode() == vakCode){
                count++;
                for(Student student: studenten){
                    totaalcijfer += student.getCijfer(v);
                }
            }
        }
        double gem = totaalcijfer/count;
        System.out.println("gemiddeld cijfer van het vak: " + vak.getModulecode() + " " + gem);
    }

    /*
    is de som van cijfers bereken
    daarna het gemmidelde bereken
    daarna de afstand tot het gemiddelde bereken en kwadrateren
    hiervan het gemmidelde bereken (variantie)
    en de wortel hiervan doen (standaarddeviatie)
    */
    public void standaardDeviatie(){
        float totaalcijfer = 0;
        float count = 0;
        float countMan = 0;
        float countVrouw = 0;
        float totaalMan = 0;
        float totaalVrouw = 0;
        for(Vak v: vakkenJaar1){
            count++;
            for(Student student: studenten){
                if(student.geslacht.equals('M')){
                    totaalMan+=student.getCijfer(v);
                    if(student.getCijfer(v)> 0){
                        countMan++;
                    }
                }
                else if(student.geslacht.equals('V')){
                    totaalVrouw+=student.getCijfer(v);
                    if(student.getCijfer(v)> 0){
                        countVrouw++;
                    }
                }
                totaalcijfer+=student.getCijfer(v);
            }
        }
        for(Vak v: vakkenJaar2){
            count++;
            for(Student student: studenten){
                if(student.geslacht.equals('M')){
                    totaalMan+=student.getCijfer(v);
                    if(student.getCijfer(v)> 0){
                        countMan++;
                    }
                }
                else if(student.geslacht.equals('V')){
                    totaalVrouw+=student.getCijfer(v);
                    if(student.getCijfer(v)> 0){
                        countVrouw++;
                    }
                }
                totaalcijfer+=student.getCijfer(v);
            }
        }
        for(Vak v: vakkenJaar3){
            count++;
            for(Student student: studenten){
                if(student.geslacht.equals('M')){
                    totaalMan+=student.getCijfer(v);
                    if(student.getCijfer(v)> 0){
                        countMan++;
                    }
                }
                else if(student.geslacht.equals('V')){
                    totaalVrouw+=student.getCijfer(v);
                    if(student.getCijfer(v)> 0){
                        countVrouw++;
                    }
                }
                totaalcijfer+=student.getCijfer(v);
            }
        }
        for(Vak v: vakkenJaar4){
            count++;
            for(Student student: studenten){
                if(student.geslacht.equals('M')){
                    totaalMan+=student.getCijfer(v);
                    if(student.getCijfer(v)> 0){
                        countMan++;
                    }
                }
                else if(student.geslacht.equals('V')){
                    totaalVrouw+=student.getCijfer(v);
                    if(student.getCijfer(v)> 0){
                        countVrouw++;
                    }
                }
                totaalcijfer+=student.getCijfer(v);
            }
        }
        float gemiddelde = totaalcijfer/count;
        float gemiddeldMan = totaalMan/countMan;
        float gemiddeldVrouw = totaalVrouw/countVrouw;
        double offGemiddelde = 0;
        for(Vak v: vakkenJaar1){
            for(Student student: studenten){
                float temp = (gemiddelde - student.getCijfer(v));
                offGemiddelde += temp*temp;
            }
        }
        for(Vak v: vakkenJaar2){
            for(Student student: studenten){
                float temp = (gemiddelde - student.getCijfer(v));
                offGemiddelde += temp*temp;
            }
        }
        for(Vak v: vakkenJaar3){
            for(Student student: studenten){
                float temp = (gemiddelde - student.getCijfer(v));
                offGemiddelde += temp*temp;
            }
        }
        for(Vak v: vakkenJaar4){
            for(Student student: studenten){
                float temp = (gemiddelde - student.getCijfer(v));
                offGemiddelde += temp*temp;
            }
        }
        double variantie = offGemiddelde / count;
        double standaardDeviatie = Math.sqrt(variantie);
        System.out.println("Standaarddeviatie van alle cijfers: " + standaardDeviatie);
        System.out.println("Variantie van alle cijfers: " + variantie);
        System.out.println("gemiddelde man: " + gemiddeldMan);
        System.out.println("Gemiddelde vrouw " + gemiddeldVrouw);
    }
}