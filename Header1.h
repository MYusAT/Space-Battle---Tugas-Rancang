#pragma once
#include <iostream>
#include <stdio.h>

struct Coor
{
	float copostx, coposty, copostz, uvx, uvy;
};

struct Indices
{
	int coorindix, coorindiy, coorindiz;
};

Coor* coorpost = new Coor[511];
Indices* indices = new Indices[717];

void scanNrVertices(FILE* nfg, Coor* coorpost)
{	//Fungsi untuk Memanggil dan Memasukan koordinat Nrverrices dari file NFG 
	int temp, NrVertices = 0;
	float normx, normy, normz, bnormx, bnormy, bnormz, tgtx, tgty, tgtz;
	fscanf_s(nfg, "NrVertices:%d", &NrVertices);
	for (int i = 0; i < NrVertices; i++) {
		fscanf_s(nfg, "   %d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];",
			&temp, &coorpost[i].copostx, &coorpost[i].coposty, &coorpost[i].copostz, &normx, &normy, &normz, &bnormx, &bnormy, &bnormz, &tgtx, &tgty, &tgtz, &coorpost[i].uvx, &coorpost[i].uvy
		);
	}
}

void scanNrIndices(FILE* nfg, Indices* indices)
{	//Fungsi untuk Memanggil dan Memasukan koordinat NrIndices dari file NFG 
	int temp, NrIndices;
	fscanf_s(nfg, "\nNrIndices:%d", &NrIndices);
	printf("%d\n", NrIndices);
	for (int i = 0; i < 717; i++)
	{
		fscanf_s(nfg, "   %d.    %d,    %d,    %d", &temp, &indices[i].coorindix, &indices[i].coorindiy, &indices[i].coorindiz);
	}
}

int load(const char* nfgPath) { //Fungsi untuk Mengecek jika bukan file nfg 
	FILE* nfg;
	fopen_s(&nfg, nfgPath, "r");
	if (!nfg) {
		printf("Ini Bukan File TGA ");
		return 0;
	}

	scanNrVertices(nfg, coorpost); //Fungsi untuk Memanggil Class scanNrIndices
	scanNrIndices(nfg, indices); //Fungsi untuk Memanggil Class scanNrIndices

	return (0);
}