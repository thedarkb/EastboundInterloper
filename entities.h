#define ENTCOUNT 4

entity ent_item(int type, int status, int lol1, int lol2);
entity ent_blobby(int lol1, int lol2, int lol3, int lol4);
entity ent_doorLocked(int tile, int flag,int filler, int filler2);

entity (*topLevelEntities[ENTCOUNT])(int,int,int,int)={
	NULL
};

char* editorEntityFlavour[ENTCOUNT]={
	"Null"
};
