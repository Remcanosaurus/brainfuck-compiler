# Brainfuck Compiler
Dit is een compiler voor Brainfuck voor Windows met extra functies.
## Building
Clone deze repository en build het project. Dubbelklik de exe in \x64\Release om het te runnen. Een .bf bestand kan dan geopend worden.
## Open met Brainfuck
Het is mogelijk om een .bf bestand direct te openen met Brainfuck. Rechtsklik op een .bf bestand en klik "Openen met...". Selecteer dan "Een app op uw PC keizen" en blader dan naar BfCompiler.exe. In de Windows Instellingen kan BfCompiler.exe ook als standaardapp ingesteld worden voor .bf bestanden. Als er dan op een .bf bestand gedubbelklikt wordt, wordt het altijd geopend in Brainfuck.
## Karakters
| **Karakter** | **Actie**                                                                                                                                                   |
| ------------ | ----------------------------------------------------------------------------------------------------------------------------------------------------------- |
| \>           | Verhoog locatie pointer.                                                                                                                                    |
| <            | Verlaag locatie pointer.                                                                                                                                    |
| +            | Verhoog de byte waar de pointer op staat.                                                                                                                   |
| \-           | Verlaag de byte waar de pointer op staat.                                                                                                                   |
| [            | Spring naar de bijbehorende ] als de byte waar de pointer op staat 0 is.                                                                                    |
| ]            | Spring naar de bijbehorende [ als de byte waar de pointer op staat niet 0 is.                                                                               |
| .            | Output de byte waar de pointer op staat als een ascii letter.                                                                                               |
| ,            | Vraag om een karakter als input en zet die als byte op het veld waar de pointer op staat.                                                                   |
| :            | Output de byte waar de pointer op staat als een getal.                                                                                                      |
| ;            | Vraag om een getal als input en zet die als byte op het veld waar de pointer op staat.                                                                      |
| /            | Output “ / “.                                                                                                                                               |
| ?            | Genereer een willekeurige byte en zet die op het veld waar de pointer op staat.                                                                             |
| {            | Definiëer een functie met als naam de waarde van de byte waar de pointer op staat.                                                                          |
| }            | Einde van een functie definitie.                                                                                                                            |
| !            | Voer de functie uit met de naam die gelijk is aan de waarde van de byte waar de pointer naar wijst.                                                         |
| \*           | Neem het aantal bytes rechts van de pointer als de waarde van de byte waar de pointer naar wijst, rijg deze bytes aan elkaar en output de waarde als getal. |
| ^            | Zet de byte in de pointer op 0, als deze al op 0 staat wordt deze 255.                                                                                      |
| #            | Comment: alles tussen twee # wordt niet door de compiler gelezen.                                                                                           |

---
Gemaakt door Remco en Thomas.
