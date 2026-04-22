#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void gestion_fichier_patient(Patient p)
{
  FILE fichier = NULL;

  fichier = fopen("pathologie_client.txt", "r");

  if
