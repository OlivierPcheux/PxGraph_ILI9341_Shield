// Version 1.0.0

//###########################################################################
//###########################################################################
//####                                                                   ####
//####                           Olivier Pécheux                         ####
//####                          Olivier@Pecheux.fr                       ####
//####                         (33) +6 69 77 82 58                       ####
//####                http://arduino.dansetrad.fr/PxGraph                ####
//####                                                                   ####
//###########################################################################
//###########################################################################

// Ceci est un complément aux pages de définition et d'explications de la
// librairie PxGraph. Ce programme illustre l'utilisation de la fonction
// writeData8() décrite dans la page  
// http://arduino.dansetrad.fr/PxGraph/writeData8.php

// Ce programme montre qu'avec les fonctions de bas niveau, on arrive à d'autres les possibilités du driver

#include <PxGraph_ILI9341_Shield.h> // Voir http://arduino.dansetrad.fr/PxGraph


const long attente = 6; // Attente entre deux décalages
int decalage=1; // Décalage de l'écran


void setup() 
{
  // Ce programme ne fonctionne qu'en mode PAYSAGE, le défilement de l'écran n'existe que sur un axe!
  setGraphMode(PAYSAGE); // Obligatoire pour utiliser l'afficheur

  // Dessin de l'avion
  clrscr(WHITE);
  if (bpxDraw("DEMOS/AVION.BPX", 0, 50) > 0) // Photo d'un avion
  { // Photo non trouvée, on fait un dessin
    clrscr(STEEL_BLUE); // Ciel
    // Définition des lignes de l'avion
    arc(121, 83, 7, DEPART_SUD + ARRIVEE_NORD, BLACK); // Cokpit
    line(118, 81, 121, 78);
    lineTo(121, 81);
    lineTo(118, 81);
    hLine(121, 198, 76); // Fuselage
    arc(198, 80, 4, DEPART_NORD + ARRIVEE_SUD);
    line(195, 84, 162, 89);
    line(121, 90, 150, 89);
    line(134, 76, 118, 53); // Aile droite
    lineTo(147, 76);
    line(140, 84, 184, 110); // Aile gauche
    lineTo(156, 83);
    line(188, 76, 211, 64); // Empennage
    lineTo(198, 76);
    line(192, 80, 200, 88);
    lineTo(196, 79);
    // Peinture de l'avion
    fill(127, 81, WHITE); // Fuselage
    fill(137, 72, WHITE); // Aile
    fill(196, 74, WHITE); // Empenage
  }
}

void loop()
{
  // Décalage de l'écran
  if (getGraphMode() == PAYSAGE)
  {
    writeRegister(0x37); writeData16(decalage++); // Décalage vertical pour un ili9341
    if (decalage == LARGEUR) decalage = 0; // Décalage complet d'un écran, on repart à 0
  }
  else if (getGraphMode() == PAYSAGE_INVERSE)
  {
    writeRegister(0x37); writeData16(--decalage); // Décalage vertical pour un ili9341
    if (decalage == 0) decalage = LARGEUR; // Décalage complet d'un écran, on repart à 0
  }
  
  // Vitesse de l'avion
  delay(attente);
} 