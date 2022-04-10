// Created by Nikita Dzer on 09.04.2022.

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../include/hashtable.h"
#include "../include/dump.h"

#undef construct_hashtable
#undef destruct_hashtable
#undef hashtable_insert
#undef hashtable_remove
#undef hashtable_search
#undef verify_hashtable

/*
#include "../include/dump.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef list_item_t  Pair;
typedef list_index_t index_t;

static FILE    *stream  = NULL;
static size_t   n_dumps = 0;

const char LIST_DOTFILE_PATH[32] = "dotfile";
const char LIST_DUMP_PATH[32] = "dump.html";

static void dump_open()
{
   if (stream == NULL)
   {
      stream = fopen(LIST_DUMP_PATH, "w");
      
      fprintf(stream,
              "<!doctype html>                                                             \n"
              "<html>                                                                      \n"
              "\t<head lang='en'>                                                          \n"
              "\t\t<meta charset='utf-8'>                                                  \n"
              "\t\t<meta name='viewport' content='width=device-width'>                     \n"
              "\t\t<title>_HtList dump</title>                                                \n"
              "\t\t<style>                                                                 \n"
              "\t\tbody {                                                                  \n"
              "\t\t\tbackground: #222222;                                                  \n"
              "\t\t\tcolor:      #DDDDDD;                                                  \n"
              "\t\t\tfont-family: Arial, sans-serif;                                       \n"
              "\t\t}                                                                       \n"
              "\t\t.list {                                                                 \n"
              "\t\t\twidth: max-content;                                                   \n"
              "\t\t\tborder: 3px solid #AAAAAA;                                            \n"
              "\t\t\tfont-size: 20px;                                                      \n"
              "\t\t\tpadding: 10px 20px;                                                   \n"
              "\t\t}                                                                       \n"
              "\t\t.img {                                                                  \n"
              "\t\t\toverflow-x: auto;                                                     \n"
              "\t\t}                                                                       \n"
              "\t\t</style>                                                                \n"
              "\t</head>                                                                   \n"
              "\t<body>                                                                    \n");
   }
}

static void dump_close()
{
   fprintf(stream,
           "\t</body>\n"
           "</html>\n");
   
   fclose(stream);
}

void list_dump_init()
{
   dump_open();
   atexit(dump_close);
}

void list_dump(const List *const p_list)
{
   const ListNode *const nodes             = p_list->nodes;
   FILE           *const dotfile           = fopen(LIST_DOTFILE_PATH, "w");
   
   fprintf(dotfile,
           "digraph G                                                                                      \n"
           "{                                                                                              \n"
           "\tbgcolor  = \"#222222\"                                                                       \n"
           "\tcompound = true                                                                              \n"
           "\tnewrank  = true                                                                              \n"
           "\tgraph[dpi = 250, splines = polyline, nodesep = 0.3, ranksep = 1, rankdir = LR]               \n"
           "\tnode[shape = box, style = \"filled\", penwidth = 2, color = \"#333333\", margin = 0.04,      \n"
           "\tfontcolor = \"white\", fontsize = 8, fillcolor = \"#666666\", fontname = \"Consolas\"]       \n"
           "\tedge[arrowsize = 0.7, style = solid, penwidth = 1.1]                                         \n"
           "\t0");
   
   for (list_index_t i = 0; i < 64; i++)
      fprintf(dotfile, " -> %lld", i);
   
   fprintf(dotfile, "[style = invis, weight = 0, minlen = \"1\"]\n");
   
   for (list_index_t i = 0; i < 64; i++)
   {
      fprintf(dotfile,
              "\tsubgraph cluster%lld                                                                              \n"
              "\t{                                                                                                 \n"
              "\t\tmargin    = 0                                                                                   \n"
              "\t\tfontcolor = \"white\"                                                                           \n"
              "\t\tfontname  = \"Consolas\"                                                                        \n"
              "\t\tbgcolor   = \"#333333\"                                                                         \n"
              "\t\tcolor     = \"#333333\"                                                                         \n"
              "\t\tpenwidth  = 2                                                                                   \n"
              "\t\tfontsize  = 8                                                                                   \n"
              "\t\tlabel     = %lld                                                                                \n"
              "\t\t%lld[shape = record, label = \"item: %s | <n>next: %lld\"]\n"
                                                                               "\t}                                                                                                 \n",
              i, i, i, nodes[i].item.key, nodes[i].next);
      
            fprintf(dotfile,
                    "\t%lld:n -> %lld:n[color = \"#87CEFA 99\"] \n",
                    i, nodes[i].next);
         
   }
   
   fprintf(dotfile, "}\n");
   fclose(dotfile);
   
   char png_path[64]    = "dump_";
   char system_cmd[128] = "dot ";
   
   sprintf(png_path,  "%zu.png", n_dumps);
   strcat(system_cmd, LIST_DOTFILE_PATH);
   strcat(system_cmd, " -Tpng -o ");
   strcat(system_cmd, png_path);
   
   system(system_cmd);
   
   fprintf(stream,
           "\t\t<hr width = '100%' >                                     \n"
           "\t\t<div class = 'list'>                                     \n"
           "\t\t\t<pre>_HtList address: %p</pre>                            \n"
           "\t\t\t<pre>Size:         %lld</pre>                          \n"
           "\t\t\t<pre>Free:         %lld</pre>                          \n"
           "\t\t\t<pre>NODS:         %p</pre>                            \n"
           "\t\t</div>                                                   \n"
           "\t\t<div class = 'img'>                                      \n"
           "\t\t\t<img src = \"%s\" height = 500px>                      \n"
           "\t\t</div>                                                   \n",
   
           p_list,
           p_list->size,
           p_list->free,
           p_list->nodes,
           png_path);
   
   n_dumps += 1;
}
 */

// ---------------------------------------------------  Structs  ------------------------------------------------------------
typedef struct _HtLog
{
    const HtHashtable *restrict ht_hashtable;
    FILE              *restrict logfile;
} _HtLog;

typedef struct _HtLogsystem
{
    _HtLog *restrict   logs;
    unsigned long long n_logs;
} _HtLogsystem;
// --------------------------------------------------- /Structs  ------------------------------------------------------------


// ---------------------------------------------------  Static constants  ------------------------------------------------------------
static const unsigned long long N_ADD_LOGS = 16;
static const char *restrict LOGFILE_PREFIX = "log_hashtable_";
// --------------------------------------------------- /Static constants  ------------------------------------------------------------


// ---------------------------------------------------  Static variables  ------------------------------------------------------------
static _HtLogsystem logsystem = {0};
// --------------------------------------------------- /Static variables  ------------------------------------------------------------


// ---------------------------------------------------  Static functions  ------------------------------------------------------------
__attribute__((constructor))
static void logsystem_construct(void)
{
    logsystem.logs = (_HtLog *)calloc(N_ADD_LOGS, sizeof(_HtLog));
    
    if (logsystem.logs == NULL)
    {
        fprintf(stderr, "Logsystem cannot allocate memory.\n");
        exit(7);
    }
}

__attribute__((destructor))
static void logsystem_destruct(void)
{
    if (logsystem.logs != NULL)
    {
        for (register unsigned long long i = 0; i < logsystem.n_logs; i++)
        {
            fflush(logsystem.logs[i].logfile); // Do we rly need flush?
            fclose(logsystem.logs[i].logfile);
        }
    }
    
    free(logsystem.logs);
}


static FILE*   create_logfile(const unsigned long long logfile_index)
{
    char temp[32] = "";
    snprintf(temp, 32, "%s%lld", LOGFILE_PREFIX, logfile_index);
    
    return fopen(temp, "w");
}

static FILE*   find_logfile(const HtHashtable *restrict ht_hashtable)
{
    for (register unsigned long long i = 0; i < logsystem.n_logs; i++)
        if (logsystem.logs[i].ht_hashtable == ht_hashtable)
            return logsystem.logs[i].logfile;
    
    return NULL;
}

static _HtLog* create_log(const HtHashtable *restrict ht_hashtable)
{
    if (logsystem.n_logs % N_ADD_LOGS == 0)
    {
        logsystem.logs = (_HtLog *)realloc(logsystem.logs, sizeof(_HtLog) * (logsystem.n_logs + N_ADD_LOGS));
        
        if (logsystem.logs == NULL)
        {
            fprintf(stderr, "Logsytem cannot reallocate memory.\n");
            exit(7);
        }
    }
    
    _HtLog *restrict log = logsystem.logs + logsystem.n_logs;
    
    log->ht_hashtable = ht_hashtable;
    log->logfile      = create_logfile(logsystem.n_logs);
    
    if (log->logfile == NULL)
    {
        fprintf(stderr, "Logsytem cannot open file %s%lld.\n", LOGFILE_PREFIX, logsystem.n_logs);
        exit(7);
    }
    
    fprintf(log->logfile,
               "*========================================================================================\n"
               "| Hashtable index:    %zu\n"
               "| Hashtable address:  %p\n"
               "|----------------------------------------------------------------------------------------\n"
               "|  CALLER     |  ARGUMENTS             |  FUNCTION        |  LINE  |  FILEPATH           \n"
               "|-------------|------------------------|------------------|--------|---------------------\n",
               logsystem.n_logs, ht_hashtable);

    logsystem.n_logs += 1;
    
    return log;
}

static FILE*   get_logfile(const HtHashtable *restrict ht_hashtable)
{
    FILE *restrict logfile = find_logfile(ht_hashtable);
    
    if (logfile == NULL)
        logfile = create_log(ht_hashtable)->logfile;
    
    return logfile;
}

static void    update_log(const HtHashtable *restrict ht_hashtable, const char *restrict format, ...)
{
    va_list ap = {0};
    
    va_start(ap, format);
    vfprintf(get_logfile(ht_hashtable), format, ap);
    va_end(ap);
}


static inline void check_hashtable(const HtHashtable *restrict ht_hashtable)
{
    if (verify_hashtable(ht_hashtable) == HT_BAD_LIST)
        update_log(ht_hashtable, "├────────── Hashtable was corrupted before next caller. ─────────────────────\n");
}
// --------------------------------------------------- /Static functions  ------------------------------------------------------------


// ---------------------------------------------------  Export functions  ------------------------------------------------------------
HtHashtable* _process_construct_hashtable(const char *restrict func, const long line, const char *restrict file)
{
    HtHashtable *restrict ht_hashtable = construct_hashtable();
    HtResult ht_result = control_hashtable();
    
    switch (ht_result)
    {
        case HT_SUCCESS:
        {
            update_log(ht_hashtable,
                       "$  construct  |                        |  %-14s  |  %-4ld  |  %-19s\n",
                       func, line, file);
            break;
        }
        
        case HT_BAD_ALLOC:
        {
            update_log(ht_hashtable,
                       ">-------------|------------------------|------------------|--------|---------------------\n"
                       ">$ construct  |                        |  %-14s  |  %-4ld  |  %-19s\n"
                       ">> Cannot allocate enough memory.\n"
                       ">-------------|------------------------|------------------|--------|---------------------\n",
                       func, line, file);
            
            break;
        }
        
        case HT_BAD_KEY:
        case HT_BAD_ARGUMENTS:
        case HT_BAD_LIST:
        default:
        {
            fprintf(stderr, "Unexpected HtResult (%d). Contact to Ht developers.\n", ht_result);
            break;
        }
    }
    
    return ht_hashtable;
}

void _process_destruct_hashtable(HtHashtable *restrict ht_hashtable,
                                 const char *restrict func, const long line, const char *restrict file)
{
    check_hashtable(ht_hashtable);
    
    destruct_hashtable(ht_hashtable);
    HtResult ht_result = control_hashtable();
    
    switch (ht_result)
    {
        case HT_SUCCESS:
        {
            update_log(ht_hashtable,
                       "#  destruct   |                        |  %-14s  |  %-4ld  |  %-19s\n",
                       func, line, file);
            break;
        }
    
        case HT_BAD_ARGUMENTS:
        {
            update_log(ht_hashtable,
                       ">-------------|------------------------|------------------|--------|---------------------\n"
                       "># destruct   |                        |  %-14s  |  %-4ld  |  %-19s\n"
                       ">> Hashtable pointer is NULL.\n"
                       ">-------------|------------------------|------------------|--------|---------------------\n",
                       func, line, file);
            break;
        }
        
        case HT_BAD_KEY:
        case HT_BAD_ALLOC:
        case HT_BAD_LIST:
        default:
        {
            fprintf(stderr, "Unexpected HtResult (%d). Contact to Ht developers.\n", ht_result);
            break;
        }
    }
}

HtValue* _process_hashtable_insert(HtHashtable *restrict ht_hashtable, const char *restrict key, const HtValue *restrict ht_value,
                                   const char *restrict func, const long line, const char *restrict file)
{
    check_hashtable(ht_hashtable);
    
    HtValue *restrict value_address = hashtable_insert(ht_hashtable, key, ht_value);
    HtResult ht_result = control_hashtable();
    
    switch (ht_result)
    {
        case HT_SUCCESS:
        {
            update_log(ht_hashtable,
                       "+  insert     |  %-20s  |  %-14s  |  %-4ld  |  %-19s\n"
                       "└─────────────|  %8p      |──────────────────|────────|─────────────────────\n",
                       key, func, line, file,
                       ht_value);
            break;
        }
    
        case HT_BAD_ARGUMENTS:
        {
            update_log(ht_hashtable,
                       ">-------------|------------------------|------------------|--------|---------------------\n"
                       ">+ insert     |  %-20s  |  %-14s  |  %-4ld  |  %-19s\n"
                       ">─────────────|  %8p      |──────────────────|────────|─────────────────────\n"
                       ">> At least one argument is NULL.\n"
                       ">-------------|------------------------|------------------|--------|---------------------\n",
                       key, func, line, file,
                       ht_value);
            break;
        }
    
        case HT_BAD_KEY:
        {
            update_log(ht_hashtable,
                       ">-------------|------------------------|------------------|--------|---------------------\n"
                       ">+ insert     |  %-20s  |  %-14s  |  %-4ld  |  %-19s\n"
                       ">─────────────|  %8p      |──────────────────|────────|─────────────────────\n"
                       ">> The key has already been in hashtable.\n"
                       ">-------------|------------------------|------------------|--------|---------------------\n",
                       key, func, line, file,
                       ht_value);
            break;
        }
        
        case HT_BAD_ALLOC:
        {
            update_log(ht_hashtable,
                       ">-------------|------------------------|------------------|--------|---------------------\n"
                       ">+ insert     |  %-20s  |  %-14s  |  %-4ld  |  %-19s\n"
                       ">─────────────|  %8p      |──────────────────|────────|─────────────────────\n"
                       ">> Cannot allocate enough memory.\n"
                       ">-------------|------------------------|------------------|--------|---------------------\n",
                       key, func, line, file,
                       ht_value);
            break;
        }
        
        case HT_BAD_LIST:
        default:
        {
            fprintf(stderr, "Unexpected HtResult (%d). Contact to Ht developers.\n", ht_result);
            break;
        }
    }
    
    return value_address;
}

HtValue* _process_hashtable_remove(HtHashtable *restrict ht_hashtable, const char *restrict key,
                                   const char *restrict func, const long line, const char *restrict file)
{
    check_hashtable(ht_hashtable);
    
    HtValue *restrict value_address = hashtable_remove(ht_hashtable, key);
    HtResult ht_result = control_hashtable();
    
    switch (ht_result)
    {
        case HT_SUCCESS:
        {
            update_log(ht_hashtable,
                       "-  remove     |  %-20s  |  %-14s  |  %-4ld  |  %-19s\n",
                       key, func, line, file);
            break;
        }
        
        case HT_BAD_ARGUMENTS:
        {
            update_log(ht_hashtable,
                       ">-------------|------------------------|------------------|--------|---------------------\n"
                       ">- remove     |  %-20s  |  %-14s  |  %-4ld  |  %-19s\n"
                       ">> At least one argument is NULL.\n"
                       ">-------------|------------------------|------------------|--------|---------------------\n",
                       key, func, line, file);
            break;
        }
        
        case HT_BAD_KEY:
        {
            update_log(ht_hashtable,
                       ">-------------|------------------------|------------------|--------|---------------------\n"
                       ">- remove     |  %-20s  |  %-14s  |  %-4ld  |  %-19s\n"
                       ">> The key is not found in hashtable.\n"
                       ">-------------|------------------------|------------------|--------|---------------------\n",
                       key, func, line, file);
            break;
        }
        
        case HT_BAD_ALLOC:
        case HT_BAD_LIST:
        default:
        {
            fprintf(stderr, "Unexpected HtResult (%d). Contact to Ht developers.\n", ht_result);
            break;
        }
    }
    
    return value_address;
}

HtValue* _process_hashtable_search(const HtHashtable *restrict ht_hashtable, const char *restrict key,
                                   const char *restrict func, const long line, const char *restrict file)
{
    check_hashtable(ht_hashtable);
    
    HtValue *restrict value_address = hashtable_search(ht_hashtable, key);
    HtResult ht_result = control_hashtable();
    
    switch (ht_result)
    {
        case HT_SUCCESS:
        {
            update_log(ht_hashtable,
                       "/  search     |  %-20s  |  %-14s  |  %-4ld  |  %-19s\n",
                       key, func, line, file);
            break;
        }
        
        case HT_BAD_ARGUMENTS:
        {
            update_log(ht_hashtable,
                       ">-------------|------------------------|------------------|--------|---------------------\n"
                       ">/ search     |  %-20s  |  %-14s  |  %-4ld  |  %-19s\n"
                       ">> At least one argument is NULL.\n"
                       ">-------------|------------------------|------------------|--------|---------------------\n",
                       key, func, line, file);
            break;
        }
        
        case HT_BAD_KEY:
        {
            update_log(ht_hashtable,
                       ">-------------|------------------------|------------------|--------|---------------------\n"
                       ">/ search     |  %-20s  |  %-14s  |  %-4ld  |  %-19s\n"
                       ">> The key is not found in hashtable.\n"
                       ">-------------|------------------------|------------------|--------|---------------------\n",
                       key, func, line, file);
            break;
        }
        
        case HT_BAD_ALLOC:
        case HT_BAD_LIST:
        default:
        {
            fprintf(stderr, "Unexpected HtResult (%d). Contact to Ht developers.\n", ht_result);
            break;
        }
    }
    
    return value_address;
}

HtResult _process_verify_hashtable(const HtHashtable *restrict ht_hashtable,
                                   const char *restrict func, const long line, const char *restrict file)
{
    HtResult ht_result = verify_hashtable(ht_hashtable);
    
    switch (ht_result)
    {
        case HT_SUCCESS:
        {
            update_log(ht_hashtable,
                       "?  verify     |                        |  %-14s  |  %-4ld  |  %-19s\n",
                       func, line, file);
            break;
        }
        
        case HT_BAD_ARGUMENTS:
        {
            update_log(ht_hashtable,
                       ">-------------|------------------------|------------------|--------|---------------------\n"
                       ">? verify     |                        |  %-14s  |  %-4ld  |  %-19s\n"
                       ">> Hashtable pointer is NULL.\n"
                       ">-------------|------------------------|------------------|--------|---------------------\n",
                       func, line, file);
            break;
        }
        
        case HT_BAD_LIST:
        {
            update_log(ht_hashtable,
                       ">-------------|------------------------|------------------|--------|---------------------\n"
                       ">? verify     |                        |  %-14s  |  %-4ld  |  %-19s\n"
                       ">> Hashtable was corrupted before this caller.\n"
                       ">-------------|------------------------|------------------|--------|---------------------\n",
                       func, line, file);
            break;
        }
        
        case HT_BAD_KEY:
        case HT_BAD_ALLOC:
        default:
        {
            fprintf(stderr, "Unexpected HtResult (%d). Contact to Ht developers.\n", ht_result);
            break;
        }
    }
    
    return ht_result;
}
// --------------------------------------------------- /Export functions  ------------------------------------------------------------