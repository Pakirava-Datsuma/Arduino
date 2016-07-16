import java.lang.reflect.Array;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

/**
 * Created by swanta on 25.06.16.
 */
public class Magnetron {
    public static void main(String[] args) {
        int duplicateCount = 0;
        String string = "<div> &nbsp;</div> <div> <div> &nbsp;</div> </div> <div> <div> <div> <hr /> <h3> <span style=\"color:#800000;\">LG: 2M219J, 2M214-01GKHLG, 2M213-01GKH, 2M226-01, M246-050GF (2M246-01GKH), 2M246050GF, 2M217J, 2M24FB-610A, 2M24FA-410A, 2M218-JF, 2M219J;</span></h3> <h3> <span style=\"color:#800000;\">Samsung: OM75S(71), OM52S61;</span></h3> <h3> <span style=\"color:#800000;\">Daewoo: 2M254J, 2M248J, 2M218JF;</span></h3> <hr /> <h3> <span style=\"color:#4b0082;\">Witol: 2M219K;</span></h3> <h3> <span style=\"color:#4b0082;\">Samsung: OM75S, OM75P;</span></h3> <h3> <span style=\"color:#4b0082;\">LG: 2M214-240GP, 6324W1A004A, 6324W1A004B, 2M219K;</span></h3> <h3> <span style=\"color:#4b0082;\">Gorenje: 264484;</span></h3> <hr /> <h3> <span style=\"color:#800000;\">Toshiba: 2M253K (JT);</span></h3> <h3> <span style=\"color:#800000;\">Witol: 2M219K;</span></h3> <h3> <span style=\"color:#800000;\">Samsung OM75S, OM75P;</span></h3> <h3> <span style=\"color:#800000;\">Panasonic: 2M210-M1;</span></h3> <h3> <span style=\"color:#800000;\">LG: 2M226-15GKH, 6324W1A004B, 2M214-240GP;</span></h3> <h3> <span style=\"color:#800000;\">Galanz: M24FB-210A;</span></h3> <hr /> <h3> <span style=\"color:#4b0082;\">LG: 2M214-01GKHLG, 2M226-15GKH, M246-050GF, 2M226-01, 2M213-01GKH;</span></h3> <h3> <span style=\"color:#4b0082;\">Daewoo: 2M218 JF;</span></h3> <h3> <span style=\"color:#4b0082;\">Galanz: 2M24FA-410A, 2M24FB-610A;</span></h3> <h3> <span style=\"color:#4b0082;\">Samsung: OM52S61, OM75S;</span></h3> <h3> <span style=\"color:#4b0082;\">Witol: 2M219J; 2M217J</span></h3> <hr /> <h3> <span style=\"color:#800000;\">LG: 2M214-01GKHLG, 2M213-01GKH, 2M226-01, M246-050GF (2M246-01GKH), 2M246 050GF, 2M217J, 2M214-21GKH;</span></h3> <h3> <span style=\"color:#800000;\">Witol: OM75S (71), OM52S61, 2M24FB-610A, 2M24FA-410A, 2M218-JF, 2M219J;</span></h3> <h3> <span style=\"color:#800000;\">Daewoo: 2M254J, 2M248J, 2M218JF;</span></h3> <hr /> <h3> <span style=\"color:#4b0082;\">LG: 2M214-01GKHLG, 2M226-15GKH, M246-050GF, 2M226-01, 2M213-01GKH;</span></h3> <h3> <span style=\"color:#4b0082;\">Daewoo: 2M218 JF;</span></h3> <h3> <span style=\"color:#4b0082;\">Galanz: 2M24FA-410A, 2M24FB-610A;&nbsp;</span></h3> <h3> <span style=\"color:#4b0082;\">Samsung: OM52S61, OM75S, OM75P31;</span></h3> <h3> <span style=\"color:#4b0082;\">Witol: 2M219J;</span></h3> <hr /> <h3> <span style=\"color:#800000;\">Daewoo: 2M218 HF;</span></h3> <h3> <span style=\"color:#800000;\">LG: 2M213-21GKH, 2M282H, 2M211A-M2, 2M214 240GP;</span></h3> <h3> <span style=\"color:#800000;\">Galanz: M24FB-210B, 2M24FA-410A;</span></h3> <hr /> <h3> <span style=\"color:#4b0082;\">Daewoo: 2M218 HF;&nbsp;</span></h3> <h3> <span style=\"color:#4b0082;\">LG: 2M213-21GKH, 2M282H, 2M211A-M2, 2M214 240GP, 2M213-GKH;</span></h3> <h3> <span style=\"color:#4b0082;\">Galanz: M24FB-210B, 2M24FA-410A;</span></h3> <hr /> <h3> <span style=\"color:#800000;\">LG: 2M213-21GKH, 2M282H, 2M211A-M2, 2M214 240GP, 2M213-GKH;</span></h3> <h3> <span style=\"color:#800000;\">Galanz: M24FB-210B, 2M24FA-410A;</span></h3> <h3> <span style=\"color:#800000;\">Daewoo: 2M218 HF;</span></h3> <hr /> <h3> <span style=\"color:#4b0082;\">Samsung: OM75S, OM75P;</span></h3> <h3> <span style=\"color:#4b0082;\">Galanz: M24FB-210B, 2M24FA-410A, M24FB-210A;</span></h3> <h3> <span style=\"color:#4b0082;\">Toshiba: 2M231H(JT)1;</span></h3> <h3> <span style=\"color:#4b0082;\">Daewoo: 2M218H-M, 2M219;</span></h3> <h3> <span style=\"color:#4b0082;\">Panasonic: 2M261-M32 (инверторный), 2M210-M1, 2M236-M42 (инверторный);</span></h3> <hr /> <h3> <span style=\"color:#800000;\">Toshiba: 2M253K (JT);</span></h3> <h3> <span style=\"color:#800000;\">Witol: 2M219K;&nbsp;</span></h3> <h3> <span style=\"color:#800000;\">Samsung: OM75S, OM75P, OM75S (10);&nbsp;</span></h3> <h3> <span style=\"color:#800000;\">Galanz: M24FB-210A;</span></h3> <h3> <span style=\"color:#800000;\">Panasonic: 2M210-M1, 2M261-M22 (инверторный);</span></h3> <h3> <span style=\"color:#800000;\">LG: 2M226-35GKH, 2M226-15GKH;</span></h3> <hr /> <h3> <span style=\"color:#4b0082;\">Daewoo: 2M218 HF;</span></h3> <h3> <span style=\"color:#4b0082;\">LG: 2M213-21GKH, 2M282H, 2M211A-M2, 2M214 240GP, 2M261-M32, 2M286-23GKH;</span></h3> <h3> <span style=\"color:#4b0082;\">Galanz: M24FB-210B, 2M24FA-410A;</span></h3> <hr /> <h3> <span style=\"color:#800000;\">Daewoo: 2M218 HF;</span></h3> <h3> <span style=\"color:#800000;\">LG: 2M213-21GKH, 2M282H, 2M211A-M2, 2M214 240GP, 2M261-M32, 2M286-23GKH, 2M809-15GKH;</span></h3> <h3> <span style=\"color:#800000;\">Galanz: M24FB-210B, 2M24FA-410A;</span></h3> <hr /> <h3> <span style=\"color:#4b0082;\">Panasonic: 2M286-23GKH, 2M236-M62J1Y, 2M261-M32;</span></h3> <h3> <span style=\"color:#4b0082;\">Daewoo: 2M218 HF;</span></h3> <h3> <span style=\"color:#4b0082;\">LG: 2M213-21GKH, 2M282H, 2M211A-M2, 2M214 240GP, 2M261-M32, 2M286-23GKH;</span></h3> <h3> <span style=\"color:#4b0082;\">Galanz: M24FB-210B, Galanz 2M24FA-410A;</span></h3> <hr /> <h3> <span style=\"color:#800000;\">Panasonic: 2M286-23GKH, 2M236-M62J1Y, 2M261-M32;</span></h3> <h3> <span style=\"color:#800000;\">Daewoo: 2M218 HF;&nbsp;</span></h3> <h3> <span style=\"color:#800000;\">LG: 2M213-21GKH, 2M282H, 2M211A-M2, 2M214 240GP, 2M261-M32, 2M286-23GKH</span></h3> <h3> <span style=\"color:#800000;\">Galanz: M24FB-210B, 2M24FA-410A;</span></h3> </div> </div> </div> <hr /> <p> &nbsp;</p>";
        String splitter = "#hr";
        string = string.replaceAll("<span[^>]+>", "\n");
        string = string.replaceAll("<hr />", splitter);

        string = string.replaceAll("<[^>]+>", "");
        string = string.replaceAll("&[^;]+;", "");
        string = string.replaceAll("  +", " ");
        List<String> strings = new LinkedList<>();
        for (String s:
                string.split(splitter)) {
            if (s.contains("M24FA-410A")) {
                for (String s2:
                     s.split("\n")) {
                    if (s2.contains("Panasonic")
                        || s2.contains("LG")
                        || s2.contains("Daewoo")
                        || s2.contains("Witol")
                        || s2.contains("Gorenje"))
                    {
                        s2 = s2.replaceFirst("^[^:]+:[  ]*", "");
                        s2 = s2.replaceFirst("[  ]*;$", "");
                        s2 = s2.replaceFirst("[  ]+", " ");
                        for (String s3:
                                s2.split(" *[,;] *"))
                        {
                            if (strings.add(s3)) {
                                duplicateCount++;
                            }
                            if (s3.contains("2M214"))
                                System.out.println(s3);
                            //System.out.println("-----------");
                        }
                    }
                }
            }

        }

        //System.out.println("\nduplicates: " + duplicateCount);
        //System.out.println(strings);
    }
}
