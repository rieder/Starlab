#ifndef  STARLAB_STORY_H
#  define  STARLAB_STORY_H

#include  "starlab_vector.h"

//----------------------------------------------------------------------
//
// Define strings to start and end various story elements.

#if 1

// Old version:

#define PARTICLE_ID	"Particle"
#define START_PARTICLE	"(Particle"
#define END_PARTICLE	")Particle"

#define DYNAMICS_ID	"Dynamics"
#define START_DYNAMICS	"(Dynamics"
#define END_DYNAMICS	")Dynamics"

#define LOG_ID		"Log"
#define START_LOG	"(Log"
#define END_LOG		")Log"

#define HYDRO_ID	"Hydro"
#define START_HYDRO	"(Hydro"
#define END_HYDRO	")Hydro"

#define STAR_ID		"Star"
#define START_STAR	"(Star"
#define END_STAR	")Star"

#else

// New short (too short?) version:

#define PARTICLE_ID	"P"
#define START_PARTICLE	"(P"
#define END_PARTICLE	")P"

#define DYNAMICS_ID	"D"
#define START_DYNAMICS	"(D"
#define END_DYNAMICS	")D"

#define LOG_ID		"L"
#define START_LOG	"(L"
#define END_LOG		")L"

#define HYDRO_ID	"H"
#define START_HYDRO	"(H"
#define END_HYDRO	")H"

#define STAR_ID		"S"
#define START_STAR	"(S"
#define END_STAR	")S"

#endif

// Note that old and new versions are *not* compatible (Steve, 10/00).
//
//----------------------------------------------------------------------

#define MAX_STORY_LINE_LENGTH 255
#define chapter_begin_char  '('
#define chapter_end_char    ')'

class story
    {
    private:

        story* next_story_node;
        story* first_daughter_node;
	story* last_daughter_node;
	char* text;
	int  chapter_flag;   // 0: this story is a line text
                             // 1: this story is a chapter

    public:

	story(int flag = 0)  // default: a bare story, to hold a text line only
	    {
	    next_story_node = first_daughter_node = last_daughter_node = NULL;
	    text = NULL;
	    chapter_flag = flag;
	    }

	~story();

	story * get_next_story_node()  {return next_story_node;}
	story * get_first_daughter_node()  {return first_daughter_node;}
	story * get_last_daughter_node()  {return last_daughter_node;}
	char * get_text()  {return text;}
	int  get_chapter_flag()   {return chapter_flag;}

	void set_next_story_node(story * s)  {next_story_node = s;}
	void set_first_daughter_node(story * s)  {first_daughter_node = s;}
	void set_last_daughter_node(story * s)  {last_daughter_node = s;}
        void set_text(char * a_string)
	    {
	    if(text != NULL)
	        delete [] text;
	    text = new char[strlen(a_string)+1];
	    strcpy(text, a_string);		  // Note that a_string
						  // isn't deleted here.
	    }

//	friend istream& operator>>(istream & , story * & );
//        friend ostream& operator<<(ostream & , story * );
    };

story* mk_story_line();
story* mk_story_line(char *);
story* mk_story_chapter();
story* mk_story_chapter(char *);

story* get_story(istream &);
story* get_story(istream &, char *);
void put_story(ostream &, story &);
void put_story_contents(ostream &, story &, char *prefix = NULL);
void put_simple_story_contents(ostream& str, story& s, char *prefix = NULL);
void put_simple_story_contents(FILE *fp, story& s, char *prefix = NULL);
void add_story_line(story *, char *);
void rm_daughter_story(story * s, story * d);

story * find_qmatch(story *, char *);
int  rmq(story *, char *);

int  getiq(story *, char *, bool verbose=false);
unsigned long  getulq(story *, char *, bool verbose=false);
real  getrq(story *, char *, bool verbose=false);
char *getsq(story *, char *, bool verbose=false);
vec  getvq(story *, char *, bool verbose=false);
void getra(story *, char *, real *, int, bool verbose=false);
void getia(story *, char *, int *, int, bool verbose=false);
void getia(story *, char *, unsigned long *, int, bool verbose=false);

void putiq(story *, char *, int);
void putulq(story *, char *, unsigned long);
void putrq(story *, char *, real, int precision = STD_PRECISION);
void putra(story *, char *, real *, int);
void putia(story *, char *, int *, int);
void putia(story *, char *, unsigned long *, int);
void putsq(story *, char *, char *);
void putvq(story *, char *, vec &, int precision = STD_PRECISION);

void dump_story(story* s, int indent = 0);

#endif
 