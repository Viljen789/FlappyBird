# Prosjekt 4102

Programmet er en versjon av det kjente spillet *Flappy Bird*, men med to ekstra varianter. Du kan altså velge å spille
som en fisk eller et romvesen, og gravitasjonen/spillmekanikken tilpasses det miljøet du spiller i.

---

## Oversikt

- **Score:** Regner ut poengsummen.
- **Game:** Lager og displayer selve spillet.
- **Bird:** Håndterer logikken med spriten.
- **Tower:** Inneholder logikken bak tårnene.
- **GameWindow:** Viser poengsummen live på skjermen.

---

## KI-verktøy

- **ChatGPT 4o** har blitt brukt til bildegenerering for alle assets, med unntak av tårnene.
- **Copilot**  ble brukt til å finne ut hvordan man kan få til at når man trykker space blir den bare registrert en
  gang, det var ett problem med romvesenet at
  den snudde seg mange ganger,og ofte ikke skiftet retning pga den snudde seg ett partall antall ganger veldig raskt,
  men
  der var løsningen å legge til en bool som registrerte om den snudde seg eller ikke, og så passe på at den bare snur
  seg
  en gang pr mellomrom trykk.

---

## Implementasjon

- **Ulike temaer:** Avhengig av om du velger fugl, fisk eller romvesen, blir gravitasjonen og spillmekanikken tilpasset
  slik at hver figur får et unikt miljø.

- **Kommentarer i koden:** Det finnes omfattende kommentarer underveis i koden som forklarer de ulike delene av
  implementasjonen.

---

