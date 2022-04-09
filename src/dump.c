//
// Created by User on 09.04.2022.
//

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