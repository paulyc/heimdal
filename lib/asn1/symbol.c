#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
RCSID("$Id$");
#include <string.h>
#include <stdlib.h>
#include "symbol.h"
#include "hash.h"

static Hashtab *htab;

static int
cmp (void *a, void *b)
{
  Symbol *s1 = (Symbol *)a;
  Symbol *s2 = (Symbol *)b;

  return strcmp (s1->name, s2->name);
}

static unsigned
hash (void *a)
{
  Symbol *s = (Symbol *)a;

  return hashjpw (s->name);
}

void
initsym ()
{
  htab = hashtabnew (101, cmp, hash);
}


void
output_name (char *s)
{
  char *p;

  for (p = s; *p; ++p)
    if (*p == '-')
      *p = '_';
}

Symbol*
addsym (char *name)
{
  Symbol key, *s;

  key.name = name;
  s = (Symbol *)hashtabsearch (htab, (void *)&key);
  if (s == NULL) {
    char *p;

    s = (Symbol *)malloc (sizeof (*s));
    s->name = name;
    s->gen_name = strdup(name);
    output_name (s->gen_name);
    s->stype = SUndefined;
    hashtabadd (htab, s);
  }
  return s;
}
