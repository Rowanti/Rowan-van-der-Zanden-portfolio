/**
 * einopdracht programmeren 4
 * Rowan van der Zanden - 1027332
 */

public class Vak {
    private String modulecode;
    private int cijfer;
    private int jaar;
    Vak(String code, int cijfer, int jaar){
        modulecode = code;
        this.cijfer = cijfer;
        this.jaar = jaar;
    }
    public String getModulecode(){
        return modulecode;
    }
    public int getCijfer(){
        return cijfer;
    }
    public int getJaar(){
        return jaar;
    }
    public void setModulecode(String code){
        modulecode = code;
    }
    public void setCijfer(int cijfer){
        this.cijfer = cijfer;
    }
    public void setJaar(int jaar){
        this.jaar = jaar;
    }
}
