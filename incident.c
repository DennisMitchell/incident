// original author: ais523
// amalgamated by: stasoid
// https://esolangs.org/wiki/Incident
// http://nethack4.org/esolangs/calesyta-2016.tar.gz
// License: GPL 3

#define DIVSUFSORT_API


/*** Start of inlined file: divsufsort.h ***/
#ifndef _DIVSUFSORT_H
#define _DIVSUFSORT_H 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <inttypes.h>

#ifndef DIVSUFSORT_API
# ifdef DIVSUFSORT_BUILD_DLL
#  define DIVSUFSORT_API __declspec(dllexport)
# else
#  define DIVSUFSORT_API __declspec(dllimport)
# endif
#endif

/*- Datatypes -*/
#ifndef SAUCHAR_T
#define SAUCHAR_T
typedef uint8_t sauchar_t;
#endif /* SAUCHAR_T */
#ifndef SAINT_T
#define SAINT_T
typedef int32_t saint_t;
#endif /* SAINT_T */
#ifndef SAIDX_T
#define SAIDX_T
typedef int32_t saidx_t;
#endif /* SAIDX_T */
#ifndef PRIdSAINT_T
#define PRIdSAINT_T PRId32
#endif /* PRIdSAINT_T */
#ifndef PRIdSAIDX_T
#define PRIdSAIDX_T PRId32
#endif /* PRIdSAIDX_T */

/*- Prototypes -*/

/**
 * Constructs the suffix array of a given string.
 * @param T[0..n-1] The input string.
 * @param SA[0..n-1] The output array of suffixes.
 * @param n The length of the given string.
 * @return 0 if no error occurred, -1 or -2 otherwise.
 */
DIVSUFSORT_API
saint_t
divsufsort(const sauchar_t *T, saidx_t *SA, saidx_t n);

/**
 * Constructs the burrows-wheeler transformed string of a given string.
 * @param T[0..n-1] The input string.
 * @param U[0..n-1] The output string. (can be T)
 * @param A[0..n-1] The temporary array. (can be NULL)
 * @param n The length of the given string.
 * @return The primary index if no error occurred, -1 or -2 otherwise.
 */
DIVSUFSORT_API
saidx_t
divbwt(const sauchar_t *T, sauchar_t *U, saidx_t *A, saidx_t n);

/**
 * Returns the version of the divsufsort library.
 * @return The version number string.
 */
DIVSUFSORT_API
const char *
divsufsort_version(void);

/**
 * Constructs the burrows-wheeler transformed string of a given string and suffix array.
 * @param T[0..n-1] The input string.
 * @param U[0..n-1] The output string. (can be T)
 * @param SA[0..n-1] The suffix array. (can be NULL)
 * @param n The length of the given string.
 * @param idx The output primary index.
 * @return 0 if no error occurred, -1 or -2 otherwise.
 */
DIVSUFSORT_API
saint_t
bw_transform(const sauchar_t *T, sauchar_t *U,
			 saidx_t *SA /* can NULL */,
			 saidx_t n, saidx_t *idx);

/**
 * Inverse BW-transforms a given BWTed string.
 * @param T[0..n-1] The input string.
 * @param U[0..n-1] The output string. (can be T)
 * @param A[0..n-1] The temporary array. (can be NULL)
 * @param n The length of the given string.
 * @param idx The primary index.
 * @return 0 if no error occurred, -1 or -2 otherwise.
 */
DIVSUFSORT_API
saint_t
inverse_bw_transform(const sauchar_t *T, sauchar_t *U,
					 saidx_t *A /* can NULL */,
					 saidx_t n, saidx_t idx);

/**
 * Checks the correctness of a given suffix array.
 * @param T[0..n-1] The input string.
 * @param SA[0..n-1] The input suffix array.
 * @param n The length of the given string.
 * @param verbose The verbose mode.
 * @return 0 if no error occurred.
 */
DIVSUFSORT_API
saint_t
sufcheck(const sauchar_t *T, const saidx_t *SA, saidx_t n, saint_t verbose);

/**
 * Search for the pattern P in the string T.
 * @param T[0..Tsize-1] The input string.
 * @param Tsize The length of the given string.
 * @param P[0..Psize-1] The input pattern string.
 * @param Psize The length of the given pattern string.
 * @param SA[0..SAsize-1] The input suffix array.
 * @param SAsize The length of the given suffix array.
 * @param idx The output index.
 * @return The count of matches if no error occurred, -1 otherwise.
 */
DIVSUFSORT_API
saidx_t
sa_search(const sauchar_t *T, saidx_t Tsize,
		  const sauchar_t *P, saidx_t Psize,
		  const saidx_t *SA, saidx_t SAsize,
		  saidx_t *left);

/**
 * Search for the character c in the string T.
 * @param T[0..Tsize-1] The input string.
 * @param Tsize The length of the given string.
 * @param SA[0..SAsize-1] The input suffix array.
 * @param SAsize The length of the given suffix array.
 * @param c The input character.
 * @param idx The output index.
 * @return The count of matches if no error occurred, -1 otherwise.
 */
DIVSUFSORT_API
saidx_t
sa_simplesearch(const sauchar_t *T, saidx_t Tsize,
				const saidx_t *SA, saidx_t SAsize,
				saint_t c, saidx_t *left);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* _DIVSUFSORT_H */

/*** End of inlined file: divsufsort.h ***/


/*** Start of inlined file: incident.h ***/
//#include <divsufsort.h>

#define INCIDENT_VERSION_STRING "0.1"

/* parse.c */
extern saint_t lexical_parse(const sauchar_t *restrict,
							 saidx_t *restrict, saidx_t);
extern saidx_t anchor_command(saidx_t *, saidx_t);

/* utils.c */
extern sauchar_t *malloc_slurp_file(const char *, saidx_t *);

/*** End of inlined file: incident.h ***/


/*** Start of inlined file: incident.c ***/
//#include "incident.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct command {
  /* The next incidence after each of the following happens: */
  saidx_t post_pop0;
  saidx_t post_pop1;
  saidx_t post_push;

  /* Intrusive list of skipped commands. (0 means not skipped.) */
  saidx_t next_skipped_after_push0;
  saidx_t next_skipped_after_push1;

  /* This command's stack. */
  saidx_t stack_height;   /* total number of elements */
  saidx_t stack_alloclen; /* allocated length of stack, in elements */
  sauchar_t *stack;       /* bottom of stack is LSB of first element */
};

struct tracedetails {
  saidx_t inputlen;
  saidx_t *parsed;
};

static char *stack_height_2_encodings[] = { u8"⇇", u8"⇆", u8"⇄", u8"⇉" };

static char *
encode_stack(saidx_t stack_height, sauchar_t *stack)
{
  if (stack_height == 0)
	return u8" ";
  if (stack_height == 1)
	return !(*stack & 1) ? u8"←" : u8"→";
  if (stack_height == 2)
	return stack_height_2_encodings[*stack & 3];
  return !(stack[(stack_height - 1) / 8] &
		   (1 << ((stack_height - 1) % 8))) ? u8"↰" : u8"↱";
}

static void
execute_commands_from(struct command *commands, saidx_t commandcount,
					  saidx_t first_incidence, saidx_t anchor,
					  struct tracedetails *trace)
{
  /* First, zero all command storage. */
  for (saidx_t i = 1; i <= commandcount; i++) {
	commands[i].next_skipped_after_push0 = 0;
	commands[i].next_skipped_after_push1 = 0;
	commands[i].stack_height = 0;
	commands[i].stack_alloclen = 0;
	commands[i].stack = NULL;
  }

  saidx_t first_skipped_incidence = 1;

  sauchar_t input_byte = 0, output_byte = 0;
  saidx_t input_bits = 0, output_bits = 0;

  /* The main command-running loop. */
  saidx_t ip = first_incidence;
  goto first_trace;
  while (ip) {
	struct command *const cmd = &(commands[ip / 3]);

	/* Ensure we have enough room to push a bit, if we're pushing. */
	if (ip % 3 != 1 && cmd->stack_alloclen <= cmd->stack_height) {
	  cmd->stack_alloclen += 32;
	  cmd->stack_alloclen *= 2;
	  cmd->stack = realloc(cmd->stack, cmd->stack_alloclen / 8);
	  if (!cmd->stack) {
		perror("could not allocate memory");
		exit(71);
	  }
	}

	switch (ip % 3) {
	case 0: /* "push 0" command */
	  if (cmd->next_skipped_after_push0) {
		/* skip the command; we end up at the post-pop0 location */
		ip = cmd->post_pop0;
		break;
	  }
	  if (ip + 1 == anchor)
		output_bits++;

	  cmd->stack[cmd->stack_height / 8] &= ~(1 << (cmd->stack_height % 8));
	  cmd->stack_height++;
	  cmd->next_skipped_after_push0 = first_skipped_incidence;
	  first_skipped_incidence = ip;
	  ip = cmd->post_push;
	  break;

	case 2: /* "push 1" command */
	  if (cmd->next_skipped_after_push1) {
		/* skip the command; we end up at the post-pop1 location */
		ip = cmd->post_pop1;
		break;
	  }
	  if (ip - 1 == anchor) {
		output_byte |= 1 << output_bits;
		output_bits++;
	  }

	  cmd->stack[cmd->stack_height / 8] |= (1 << (cmd->stack_height % 8));
	  cmd->stack_height++;
	  cmd->next_skipped_after_push1 = first_skipped_incidence;
	  first_skipped_incidence = ip;
	  ip = cmd->post_push;
	  break;

	case 1: /* "pop" command */

	  /* Clear the list of skipped incidences. */
	  while (first_skipped_incidence != 1) {
		saidx_t *next_skipped = first_skipped_incidence % 3 ?
		  &(commands[first_skipped_incidence / 3].next_skipped_after_push1) :
		  &(commands[first_skipped_incidence / 3].next_skipped_after_push0);
		first_skipped_incidence = *next_skipped;
		*next_skipped = 0;
	  }

	  /* If the stack's empty, read user input. */
	  if (cmd->stack_height == 0) {
		if (input_bits == 0) {
		  int c = getchar();
		  if (c < 0) {
			/* if we have no stack elements and input's at EOF, then skip
			   the pop command */
			ip = cmd->post_push;
			break;
		  }

		  input_byte = c;
		  input_bits = 8;
		}

		if (input_byte & 1)
		  ip = cmd->post_pop1;
		else
		  ip = cmd->post_pop0;
		input_byte >>= 1;
		input_bits--;

		break;
	  }

	  /* Pop the stack, and move the IP accordingly. */
	  cmd->stack_height--;
	  if (cmd->stack[cmd->stack_height / 8] & (1 << (cmd->stack_height % 8)))
		ip = cmd->post_pop1;
	  else
		ip = cmd->post_pop0;
	  break;
	}

  first_trace:
	if (trace) {
	  for (saidx_t i = 0; i < trace->inputlen; i++) {
		saidx_t c = trace->parsed[i];
		if (c <= 2)
		  printf("%s", u8"░");
		else if (c == ip)
		  printf("%s", u8"▶");
		else if ((c % 3) == 1)
		  printf("%s", encode_stack(commands[c / 3].stack_height,
									commands[c / 3].stack));
		else
		  printf("%s", !((c % 3 == 2)
						 ? commands[c / 3].next_skipped_after_push1
						 : commands[c / 3].next_skipped_after_push0)
				 ? u8"✓" : u8"✗");
	  }
	  if (output_bits == 8)
		putchar(' ');
	}

	if (output_bits == 8) {
	  putchar(output_byte);
	  output_bits = 0;
	  output_byte = 0;
	}

	if (trace) {
	  putchar('\n');
	}
  }

  /* Deallocate the allocated parts of command storage. */
  for (saidx_t i = 1; i <= commandcount; i++) {
	free(commands[i].stack);
	commands[i].stack = NULL;
	commands[i].stack_alloclen = 0;
  }
}

int
main(int argc, char **argv)
{
  bool trace = false;
  bool fragmented = false;

  while (argc > 1 && *(argv[1]) == '-') {
	switch (argv[1][1]) {
	case 't':
	  trace = true;
	  break;
	case 'f':
	  fragmented = true;
	  break;
	case '-':
	  if (!strcmp(argv[1], "--version")) {
		puts("incident version " INCIDENT_VERSION_STRING);
		return 0;
	  } else if (!strcmp(argv[1], "--")) {
		argc--;
		argv++;
		goto stop_parsing_options;
	  }
	  /* otherwise either it's --help or it's unrecognised;
		 fall through either way */
	default:
	usage:
	  puts("Usage: incident [options] program");
	  puts("Interprets the given Incident program.");
	  puts("Available options:");
	  puts("  -t  Display detailed trace output");
	  puts("  -f  Debug a program fragment (start at ^, end at $)");
	  return (argc != 2 || strcmp(argv[1], "--help")) ? 64 : 0;
	}
	argc--;
	argv++;
  }
stop_parsing_options:
  ;

  if (argc != 2)
	goto usage;

  saidx_t inputlen = 0;
  sauchar_t *input = malloc_slurp_file(argv[1], &inputlen);
  if (!input)
	return inputlen; /* malloc_slurp_file prints the error message */

  /* Lexically parse the input. */
  saidx_t parsed[inputlen];
  saint_t commandcount = lexical_parse(input, parsed, inputlen);
  if (commandcount < 0) {
	fprintf(stderr, "internal error: cannot parse program");
	free(input);
	return 70;
  }

  saidx_t anchor = anchor_command(parsed, inputlen);

  /* Populate a list of commands. */
  struct command commands[commandcount + 1];
  saidx_t first_incidence = 0;
  saidx_t *store_next_command_in = &first_incidence;
  for (saidx_t i = 0; i < inputlen; i++) {
	if (fragmented && input[i] == '$') {
	  *store_next_command_in = 0; /* we stop running at $ in fragmented mode */
	  store_next_command_in = NULL;

	} else if (parsed[i] > 2) {
	  /* Store the command in the place we designated for it. */
	  if (store_next_command_in)
		*store_next_command_in = parsed[i];

	  /* Work out where to store the next command. */
	  switch (parsed[i] % 3) {
	  case 0: /* enter: push 0; leave: popped 0 */
		store_next_command_in = &(commands[parsed[i]/3].post_pop0);
		break;
	  case 1: /* enter: pop; leave: pushed something */
		store_next_command_in = &(commands[parsed[i]/3].post_push);
		break;
	  case 2: /* enter: push 1; leave: popped 1 */
		store_next_command_in = &(commands[parsed[i]/3].post_pop1);
	  }

	  /* Skip future bytes of the command. */
	  while (i + 1 < inputlen && parsed[i+1] == parsed[i] &&
			 (!fragmented || parsed[i+1] != '$'))
		i++;
	}
  }

  if (store_next_command_in)
	*store_next_command_in = 0;

  struct tracedetails td = {inputlen, parsed};
  struct tracedetails *tdp = trace ? &td : NULL;

  if (!fragmented)
	execute_commands_from(commands, commandcount, first_incidence, anchor, tdp);
  else {
	for (saidx_t i = 0; i < inputlen; i++) {
	  if (input[i] == '^') {
		while (i < inputlen && parsed[i] <= 2)
		  i++;
		if (i < inputlen) {
		  execute_commands_from(commands, commandcount, parsed[i], anchor, tdp);
		  putchar('\n');
		}
	  }
	}
  }

  free(input);
  return 0;
}

/*** End of inlined file: incident.c ***/


/*** Start of inlined file: parse.c ***/
//#include "incident.h"

#include <stdio.h>
#include <stdlib.h>

/* The general rules of parsing Incident are fairly simple: identify all
   substrings that appear exactly three times and aren't contained in a larger
   such substring (provisional commands) and the locations of those substrings
   within the string (provisional incidences); then whenever two provisional
   incidences overlap, delete both the corresponding commands from the list of
   provisional commands to produce a final list of commands.

   In order to identify substrings that have exactly three incidences, we first
   use libdivsufsort to produce a suffix array (which has the property that if
   you take the first n characters of each suffix in the array, you get a list
   of n-character substrings of the input in sorted order). Then we create an
   LCP array (which lists the number of characters that each suffix shares in
   common with the subsequent suffix). Then we find substrings with exactly
   three incidences via looking for sequences [a,b,c,d] in the LCP array for
   which b and c are both larger than both a and d. */

struct incidence {
  saidx_t start;
  saidx_t length;
};

/* Produce an LCP array and suffix array for a given input string.

   The output is written into the arrays at suffixarray and lcparray, which must
   be pre-allocated to inputlength and inputlength - 1 elements respectively.

   Returns 0 on success, negative on failure. */
static saint_t
suffixlcp(const sauchar_t *restrict input, saidx_t *restrict suffixarray,
		  saidx_t *restrict lcparray, saidx_t inputlength)
{
  /* Sanity check: an LCP array requires a nonempty input string because
	 otherwise it'd have negatively many elements */
  if (inputlength <= 0)
	return -3;

  /* Use divsufsort to produce the suffix array. */
  saint_t rv = divsufsort(input, suffixarray, inputlength);
  if (rv < 0)
	return rv;

  /* This algorithm is taken from /Linear-Time Longest-Common-Prefix
	 Computation in Suffix Arrays and its Implications/ (Kasai, Lee, Arimura,
	 Arikawa, Park 2001), and was converted to C99 by Alex Smith. */
  saidx_t rank[inputlength];
  saidx_t h = 0;

  for (saidx_t i = 0; i < inputlength; i++)
	rank[suffixarray[i]] = i;

  for (saidx_t i = 0; i < inputlength; i++) {
	if (rank[i] == 0)
	  continue;

	saidx_t j = suffixarray[rank[i] - 1];
	while (i + h < inputlength && j + h < inputlength &&
		   input[i + h] == input[j + h])
	  h++;
	lcparray[rank[i] - 1] = h;
	if (h > 0)
	  h--;
  }

  return 0;
}

/* Given an LCP array and suffix array, identify all provisional commands within
   it and all incidences of those provisional commands. (A provisional command
   is a string that has exactly three incidences.) Provisional commands won't be
   returned if they're substrings of a longer command.

   Returns the number of provisional commands. (There is no failure state; the
   caller has to verify that the input is long enough to have a meaningful LCP
   array.) The output is written into the given output array, which must be long
   enough to hold all the incidences (recommended length: equal to that of the
   input array); to get a list of provisional commands, take every third
   incidence. */
static saidx_t
find_commands_and_incidences(
  const sauchar_t *restrict input, const saidx_t *restrict suffixarray,
  const saidx_t *restrict lcparray,
  struct incidence *restrict incidences, saidx_t inputlength)
{
  saidx_t incidencecount = 0;
  for (int i = 0; i < inputlength - 2; i++) {
	/* To have exactly 3 incidences, the LCP array needs a pattern of
	   (i-1) short, (i) long, (i+1) long, (i+2) short. "Out of bounds" in the
	   LCP array is effectively the same as 0, so we have inputlength - 2
	   positions (the LCP array has inputlength - 1 positions, and we
	   subtract 1 because i+1 has to be inbounds too). */
	saidx_t longerboundary = (i == 0 ? 0 : lcparray[i-1]);
	if (i < inputlength - 3 && longerboundary < lcparray[i+2])
	  longerboundary = lcparray[i+2];
	saidx_t shorterinner = lcparray[i+1];
	if (lcparray[i] < shorterinner)
	  shorterinner = lcparray[i];

	if (shorterinner <= longerboundary)
	  continue;

	/* The substrings starting at suffixarray[i, i+1, i+2] with length
	   shorterinner will all be identical (because their first shorterinner
	   characters are identical via the definition of the LCP array), and there
	   will be no other incidences of them (because such an incidence would have
	   to appear next to the others in the suffix array, but the LCP array says
	   that no more than longerboundary characters match at the start). We also
	   know that the substring is not a prefix of a longer provisional command
	   (because otherwise longerboundary would be higher). It might be a suffix
	   of a longer provisional command, though; to discount this we need to look
	   at the preceding characters in the input and make sure they aren't all
	   the same. */
	if (suffixarray[i] > 0 && suffixarray[i+1] > 0 && suffixarray[i+2] > 0 &&
		input[suffixarray[i] - 1] == input[suffixarray[i+1] - 1] &&
		input[suffixarray[i] - 1] == input[suffixarray[i+2] - 1])
	  continue;

	/* OK, it's definitely a provisional command. Record it. */
	incidences[incidencecount++] =
	  (struct incidence){.start = suffixarray[i],   .length = shorterinner};
	incidences[incidencecount++] =
	  (struct incidence){.start = suffixarray[i+1], .length = shorterinner};
	incidences[incidencecount++] =
	  (struct incidence){.start = suffixarray[i+2], .length = shorterinner};
  }

  return incidencecount / 3; /* no way to fail */
}

/* Parses the input as an Incident program. The input is a sequence of
   octets in (input, inputlength). The output lists a lexical category
   for each octet of the input:

   0 - not part of an incidence of a command or provisional command
   1 - part of an incidence of one non-command provisional command
   2 - part of an incidence of multiple provisional commands

   Higher numbers represent incidences of (non-provisional) commands.
   These use arbitrary numbers >= 2, but incidences of the same command
   will have the same value / 3, and the value % 3 gives the position:

   0 - first incidence;
   1 - middle incidence;
   2 - last incidence.

   Returns the number of non-provisional commands seen on success, negative on
   failure. */
saint_t
lexical_parse(const sauchar_t *restrict input, saidx_t *restrict parsed,
			  saidx_t inputlength)
{
  /* Initialize the output to all zeroes. */
  for (saidx_t i = 0; i < inputlength; i++)
	parsed[i] = 0;

  /* Special case: very short inputs can't go through the normal codepaths
	 because the VLAs would be too small, but they also can't contain any
	 even provisional commands and thus are trivial to parse. */
  if (inputlength < 3)
	return 0;

  saidx_t suffixarray[inputlength];
  saidx_t lcparray[inputlength - 1];
  struct incidence incidences[inputlength];

  /* Find the commands and their incidences. */
  saint_t rv = suffixlcp(input, suffixarray, lcparray, inputlength);
  if (rv < 0)
	return rv;
  saidx_t commands = find_commands_and_incidences(
	input, suffixarray, lcparray, incidences, inputlength);

  /* Record a mapping between "old" and "new" command numbers. "old" number =
	 key = location in the incidences array divided by 3. "new" number = value =
	 0 for deleted, 1 for "value hasn't been determined yet", otherwise a
	 nonzero multiple of 3 with an adjustment:
	 -1: no incidences processed yet;
	 +0: first  incidence is being processed or has been processed;
	 +1: second incidence is being processed or has been processed;
	 +2: third  incidence is being processed or has been processed */
  saidx_t newnumbers[commands < 1 ? 1 : commands];

  /* Loop over the incidences, marking them in parsed as we go. A 0 gets
	 converted to a temporary new command number, equal to the old command
	 number plus 1 times 3 (plus 1 if it's the first octet of the incidence;
	 this allows us to distinguish between two identical incidences).  Anything
	 that's already nonzero gets converted to 2 (to mark that this is where an
	 overlap occurred). */
  for (saidx_t i = 0; i < commands * 3; i++) {
	unsigned old_command_number = i / 3;

	if (!(i % 3))
	  newnumbers[old_command_number] = old_command_number + 1;

	for (saidx_t j = incidences[i].start;
		 j < incidences[i].start + incidences[i].length; j++) {
	  if (parsed[j]) {
		/* The overlap deletes both overlapping commands; this one is
		   old_command_number; the other might be parsed[j] / 3 - 1, or might be
		   a command that's been deleted already. */
		if (parsed[j] != 2)
		  newnumbers[parsed[j] / 3 - 1] = 0;
		newnumbers[old_command_number] = 0;
		parsed[j] = 2;
	  } else {
		parsed[j] = (old_command_number + 1) * 3;
	  }
	}

	if (parsed[incidences[i].start] > 2)
	  parsed[incidences[i].start]++;
  }

  /* Assign arbitrary command numbers, keeping the numbers as low as
	 possible. */
  saidx_t newnumber = 2;
  for (saidx_t i = 0; i < commands; i++) {
	if (!newnumbers[i])
	  continue;
	newnumbers[i] = newnumber;
	newnumber += 3;
  }

  /* Now loop over the input, differentiating the three incidences of each
	 command. */
  for (saidx_t i = 0; i < inputlength; i++) {
	if (parsed[i] < 3)
	  continue; /* it's already correctly 0 or 2 */

	unsigned old_command_number = parsed[i] / 3 - 1;
	if (!newnumbers[old_command_number]) {
	  parsed[i] = 1; /* the command was deleted due to overlap */
	  continue;
	}

	if (parsed[i] % 3) /* first octet of an instance */
	  newnumbers[old_command_number]++; /* maintain the invariant */
	parsed[i] = newnumbers[old_command_number];
  }

  return newnumber / 3; /* remainder is necessarily 2 */
}

/* Given a parsed input program, returns the anchor command (as the incidence
   number of the second incidence of the command). parsedlen is the number of
   elements in parsed (i.e. the number of octets in the original program). */
saidx_t
anchor_command(saidx_t *parsed, saidx_t parsedlen)
{
  /* First scan over the program: count the command incidences. */
  saidx_t last_incidence = 0;
  saidx_t incidence_count = 0;

  for (saidx_t i = 0; i < parsedlen; i++) {
	if (parsed[i] > 2 && parsed[i] != last_incidence) {
	  last_incidence = parsed[i];
	  incidence_count++;
	}
  }

  if (incidence_count == 0)
	return 0; /* no anchor command */

  /* Second scan: find the centremost incidence. With 1 or 2 incidences, this
	 is the first; with 3 or 4, this is the second; and so on. */
  saidx_t target_incidence = (incidence_count - 1) / 2;
  incidence_count = 0;

  for (saidx_t i = 0; i < parsedlen; i++) {
	if (parsed[i] > 2 && parsed[i] != last_incidence) {
	  if (incidence_count == target_incidence) {
		/* Be careful: this might be the first or third incidence. */
		return (parsed[i] / 3) * 3 + 1;
	  }

	  last_incidence = parsed[i];
	  incidence_count++;
	}
  }
  abort(); /* we missed it? */
}

#if defined(TEST) && TEST == 1
int
main(void)
{
  const sauchar_t testinput[] =
	"aaabcbcbcdefdfefedghijghighjkllkklmmmmonono-nonppqpq-pqprsrsrstststuvuvu";
#define TESTLENGTH (sizeof testinput - 1) /* remove the NUL */
  saidx_t suffixarray[TESTLENGTH];
  saidx_t lcparray[TESTLENGTH - 1];

  saint_t rv = suffixlcp(testinput, suffixarray, lcparray, TESTLENGTH);
  if (rv < 0) {
	fprintf(stderr, "suffixlcp failed: error code %d\n", rv);
	return 70;
  }

  for (saidx_t i = 0; i < TESTLENGTH; i++) {
	printf("%4u%4u%4u %.4s\n", (unsigned)i, (unsigned)suffixarray[i],
		   i == TESTLENGTH - 1 ? 0 : (unsigned)lcparray[i],
		   testinput + suffixarray[i]);
  }

  printf("\n");

  struct incidence incidences[TESTLENGTH];
  saidx_t commands = find_commands_and_incidences(
	testinput, suffixarray, lcparray, incidences, TESTLENGTH);

  for (saidx_t i = 0; i < commands * 3; i++) {
	printf("%4d%4u%4u %.*s\n", (int)(i/3), (unsigned)incidences[i].start,
		   (unsigned)incidences[i].length, (int)incidences[i].length,
		   testinput + incidences[i].start);
  }

  printf("\n");

  saidx_t parsed[TESTLENGTH];
  rv = lexical_parse(testinput, parsed, TESTLENGTH);
  if (rv < 0) {
	fprintf(stderr, "lexical_parse failed: error code %d\n", rv);
	return 70;
  }

  for (unsigned i = 0; i < TESTLENGTH; i++) {
	printf("%4u %c%4u\n", i, testinput[i], (unsigned)parsed[i]);
  }

  printf("\n");

  return 0;
}
#endif

/*** End of inlined file: parse.c ***/


/*** Start of inlined file: utils.c ***/
//#include "incident.h"

#include <stdio.h>
#include <stdlib.h>

/* length is an out parameter in which the file's length is stored;
   NULL filename slurps standard input; on error, prints an error
   message to standard error and returns NULL, with an error code in
   *length; otherwise, returns a malloc'ed array holding the file's
   contents */
sauchar_t *
malloc_slurp_file(const char *filename, saidx_t *length)
{
  FILE *infile = stdin;
  if (filename) {
	if (!((infile = fopen(filename, "rb")))) {
	  perror(filename);
	  *length = 66;
	  return NULL;
	}
  }

  /* Now slurp the input. */
  saidx_t inputalloc = 0;
  saidx_t inputlen = 0;
  sauchar_t *input = 0;
  for (;;) {
	int c = getc(infile);
	if (c == EOF) {
	  if (feof(infile)) {
		break;
	  } else { /* ferror(infile) */
		perror("reading input file");
		free(input);
		if (infile != stdin)
		  fclose(infile);
		*length = 66;
		return NULL;
	  }
	}

	if (inputlen == inputalloc) {
	  inputalloc += 8;
	  inputalloc *= 16;
	  sauchar_t *newinput = realloc(input, inputalloc);
	  if (!newinput) {
		perror("allocating memory");
		*length = 71;
		if (infile != stdin)
		  fclose(infile);
		free(input);
		return NULL;
	  } else {
		input = newinput;
	  }
	}

	input[inputlen++] = (sauchar_t)c;
  }

  *length = inputlen;
  if (infile != stdin)
	fclose(infile);
  return input;
}

/*** End of inlined file: utils.c ***/


/*** Start of inlined file: mydivsufsort2.c ***/

/*** Start of inlined file: config.h ***/
#ifndef _CONFIG_H
#define _CONFIG_H 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** Define to the version of this package. **/
#define PROJECT_VERSION_FULL "2.0.2-1"

/** Define to 1 if you have the header files. **/
#define HAVE_INTTYPES_H 1
#define HAVE_STDDEF_H 1
#define HAVE_STDINT_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STRING_H 1
/* #undef HAVE_STRINGS_H */
#define HAVE_MEMORY_H 1
#define HAVE_SYS_TYPES_H 1

/** for WinIO **/
#define HAVE_IO_H 1
#define HAVE_FCNTL_H 1
#define HAVE__SETMODE 1
/* #undef HAVE_SETMODE */
#define HAVE__FILENO 1
#define HAVE_FOPEN_S 1
#define HAVE__O_BINARY 1
#ifndef HAVE__SETMODE
# if HAVE_SETMODE
#  define _setmode setmode
#  define HAVE__SETMODE 1
# endif
# if HAVE__SETMODE && !HAVE__O_BINARY
#  define _O_BINARY 0
#  define HAVE__O_BINARY 1
# endif
#endif

/** for inline **/
#ifndef INLINE
# define INLINE inline
#endif

/** for VC++ warning **/
#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* _CONFIG_H */

/*** End of inlined file: config.h ***/


/*** Start of inlined file: divsufsort_private.h ***/
#ifndef _DIVSUFSORT_PRIVATE_H
#define _DIVSUFSORT_PRIVATE_H 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if HAVE_CONFIG_H
# include "config.h"
#endif
#include <assert.h>
#include <stdio.h>
#if HAVE_STRING_H
# include <string.h>
#endif
#if HAVE_STDLIB_H
# include <stdlib.h>
#endif
#if HAVE_MEMORY_H
# include <memory.h>
#endif
#if HAVE_STDDEF_H
# include <stddef.h>
#endif
#if HAVE_STRINGS_H
# include <strings.h>
#endif
#if HAVE_INTTYPES_H
# include <inttypes.h>
#else
# if HAVE_STDINT_H
#  include <stdint.h>
# endif
#endif
#if defined(BUILD_DIVSUFSORT64)
# include "divsufsort64.h"
# ifndef SAIDX_T
#  define SAIDX_T
#  define saidx_t saidx64_t
# endif /* SAIDX_T */
# ifndef PRIdSAIDX_T
#  define PRIdSAIDX_T PRIdSAIDX64_T
# endif /* PRIdSAIDX_T */
# define divsufsort divsufsort64
# define divbwt divbwt64
# define divsufsort_version divsufsort64_version
# define bw_transform bw_transform64
# define inverse_bw_transform inverse_bw_transform64
# define sufcheck sufcheck64
# define sa_search sa_search64
# define sa_simplesearch sa_simplesearch64
# define sssort sssort64
# define trsort trsort64
#else
//# include "divsufsort.h"
#endif

/*- Constants -*/
#if !defined(UINT8_MAX)
# define UINT8_MAX (255)
#endif /* UINT8_MAX */
#if defined(ALPHABET_SIZE) && (ALPHABET_SIZE < 1)
# undef ALPHABET_SIZE
#endif
#if !defined(ALPHABET_SIZE)
# define ALPHABET_SIZE (UINT8_MAX + 1)
#endif
/* for divsufsort.c */
#define BUCKET_A_SIZE (ALPHABET_SIZE)
#define BUCKET_B_SIZE (ALPHABET_SIZE * ALPHABET_SIZE)
/* for sssort.c */
#if defined(SS_INSERTIONSORT_THRESHOLD)
# if SS_INSERTIONSORT_THRESHOLD < 1
#  undef SS_INSERTIONSORT_THRESHOLD
#  define SS_INSERTIONSORT_THRESHOLD (1)
# endif
#else
# define SS_INSERTIONSORT_THRESHOLD (8)
#endif
#if defined(SS_BLOCKSIZE)
# if SS_BLOCKSIZE < 0
#  undef SS_BLOCKSIZE
#  define SS_BLOCKSIZE (0)
# elif 32768 <= SS_BLOCKSIZE
#  undef SS_BLOCKSIZE
#  define SS_BLOCKSIZE (32767)
# endif
#else
# define SS_BLOCKSIZE (1024)
#endif
/* minstacksize = log(SS_BLOCKSIZE) / log(3) * 2 */
#if SS_BLOCKSIZE == 0
# if defined(BUILD_DIVSUFSORT64)
#  define SS_MISORT_STACKSIZE (96)
# else
#  define SS_MISORT_STACKSIZE (64)
# endif
#elif SS_BLOCKSIZE <= 4096
# define SS_MISORT_STACKSIZE (16)
#else
# define SS_MISORT_STACKSIZE (24)
#endif
#if defined(BUILD_DIVSUFSORT64)
# define SS_SMERGE_STACKSIZE (64)
#else
# define SS_SMERGE_STACKSIZE (32)
#endif
/* for trsort.c */
#define TR_INSERTIONSORT_THRESHOLD (8)
#if defined(BUILD_DIVSUFSORT64)
# define TR_STACKSIZE (96)
#else
# define TR_STACKSIZE (64)
#endif

/*- Macros -*/
#ifndef SWAP
# define SWAP(_a, _b) do { t = (_a); (_a) = (_b); (_b) = t; } while(0)
#endif /* SWAP */
#ifndef MIN
# define MIN(_a, _b) (((_a) < (_b)) ? (_a) : (_b))
#endif /* MIN */
#ifndef MAX
# define MAX(_a, _b) (((_a) > (_b)) ? (_a) : (_b))
#endif /* MAX */
#define STACK_PUSH(_a, _b, _c, _d)\
  do {\
	assert(ssize < STACK_SIZE);\
	stack[ssize].a = (_a), stack[ssize].b = (_b),\
	stack[ssize].c = (_c), stack[ssize++].d = (_d);\
  } while(0)
#define STACK_PUSH5(_a, _b, _c, _d, _e)\
  do {\
	assert(ssize < STACK_SIZE);\
	stack[ssize].a = (_a), stack[ssize].b = (_b),\
	stack[ssize].c = (_c), stack[ssize].d = (_d), stack[ssize++].e = (_e);\
  } while(0)
#define STACK_POP(_a, _b, _c, _d)\
  do {\
	assert(0 <= ssize);\
	if(ssize == 0) { return; }\
	(_a) = stack[--ssize].a, (_b) = stack[ssize].b,\
	(_c) = stack[ssize].c, (_d) = stack[ssize].d;\
  } while(0)
#define STACK_POP5(_a, _b, _c, _d, _e)\
  do {\
	assert(0 <= ssize);\
	if(ssize == 0) { return; }\
	(_a) = stack[--ssize].a, (_b) = stack[ssize].b,\
	(_c) = stack[ssize].c, (_d) = stack[ssize].d, (_e) = stack[ssize].e;\
  } while(0)
/* for divsufsort.c */
#define BUCKET_A(_c0) bucket_A[(_c0)]
#if ALPHABET_SIZE == 256
#define BUCKET_B(_c0, _c1) (bucket_B[((_c1) << 8) | (_c0)])
#define BUCKET_BSTAR(_c0, _c1) (bucket_B[((_c0) << 8) | (_c1)])
#else
#define BUCKET_B(_c0, _c1) (bucket_B[(_c1) * ALPHABET_SIZE + (_c0)])
#define BUCKET_BSTAR(_c0, _c1) (bucket_B[(_c0) * ALPHABET_SIZE + (_c1)])
#endif

/*- Private Prototypes -*/
/* sssort.c */
void
sssort(const sauchar_t *Td, const saidx_t *PA,
	   saidx_t *first, saidx_t *last,
	   saidx_t *buf, saidx_t bufsize,
	   saidx_t depth, saidx_t n, saint_t lastsuffix);
/* trsort.c */
void
trsort(saidx_t *ISA, saidx_t *SA, saidx_t n, saidx_t depth);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* _DIVSUFSORT_PRIVATE_H */

/*** End of inlined file: divsufsort_private.h ***/


/*** Start of inlined file: divsufsort.c ***/
//#include "divsufsort_private.h"
#ifdef _OPENMP
# include <omp.h>
#endif

/*- Private Functions -*/

/* Sorts suffixes of type B*. */
static
saidx_t
sort_typeBstar(const sauchar_t *T, saidx_t *SA,
			   saidx_t *bucket_A, saidx_t *bucket_B,
			   saidx_t n) {
  saidx_t *PAb, *ISAb, *buf;
#ifdef _OPENMP
  saidx_t *curbuf;
  saidx_t l;
#endif
  saidx_t i, j, k, t, m, bufsize;
  saint_t c0, c1;
#ifdef _OPENMP
  saint_t d0, d1;
  int tmp;
#endif

  /* Initialize bucket arrays. */
  for(i = 0; i < BUCKET_A_SIZE; ++i) { bucket_A[i] = 0; }
  for(i = 0; i < BUCKET_B_SIZE; ++i) { bucket_B[i] = 0; }

  /* Count the number of occurrences of the first one or two characters of each
	 type A, B and B* suffix. Moreover, store the beginning position of all
	 type B* suffixes into the array SA. */
  for(i = n - 1, m = n, c0 = T[n - 1]; 0 <= i;) {
	/* type A suffix. */
	do { ++BUCKET_A(c1 = c0); } while((0 <= --i) && ((c0 = T[i]) >= c1));
	if(0 <= i) {
	  /* type B* suffix. */
	  ++BUCKET_BSTAR(c0, c1);
	  SA[--m] = i;
	  /* type B suffix. */
	  for(--i, c1 = c0; (0 <= i) && ((c0 = T[i]) <= c1); --i, c1 = c0) {
		++BUCKET_B(c0, c1);
	  }
	}
  }
  m = n - m;
/*
note:
  A type B* suffix is lexicographically smaller than a type B suffix that
  begins with the same first two characters.
*/

  /* Calculate the index of start/end point of each bucket. */
  for(c0 = 0, i = 0, j = 0; c0 < ALPHABET_SIZE; ++c0) {
	t = i + BUCKET_A(c0);
	BUCKET_A(c0) = i + j; /* start point */
	i = t + BUCKET_B(c0, c0);
	for(c1 = c0 + 1; c1 < ALPHABET_SIZE; ++c1) {
	  j += BUCKET_BSTAR(c0, c1);
	  BUCKET_BSTAR(c0, c1) = j; /* end point */
	  i += BUCKET_B(c0, c1);
	}
  }

  if(0 < m) {
	/* Sort the type B* suffixes by their first two characters. */
	PAb = SA + n - m; ISAb = SA + m;
	for(i = m - 2; 0 <= i; --i) {
	  t = PAb[i], c0 = T[t], c1 = T[t + 1];
	  SA[--BUCKET_BSTAR(c0, c1)] = i;
	}
	t = PAb[m - 1], c0 = T[t], c1 = T[t + 1];
	SA[--BUCKET_BSTAR(c0, c1)] = m - 1;

	/* Sort the type B* substrings using sssort. */
#ifdef _OPENMP
	tmp = omp_get_max_threads();
	buf = SA + m, bufsize = (n - (2 * m)) / tmp;
	c0 = ALPHABET_SIZE - 2, c1 = ALPHABET_SIZE - 1, j = m;
#pragma omp parallel default(shared) private(curbuf, k, l, d0, d1, tmp)
	{
	  tmp = omp_get_thread_num();
	  curbuf = buf + tmp * bufsize;
	  k = 0;
	  for(;;) {
		#pragma omp critical(sssort_lock)
		{
		  if(0 < (l = j)) {
			d0 = c0, d1 = c1;
			do {
			  k = BUCKET_BSTAR(d0, d1);
			  if(--d1 <= d0) {
				d1 = ALPHABET_SIZE - 1;
				if(--d0 < 0) { break; }
			  }
			} while(((l - k) <= 1) && (0 < (l = k)));
			c0 = d0, c1 = d1, j = k;
		  }
		}
		if(l == 0) { break; }
		sssort(T, PAb, SA + k, SA + l,
			   curbuf, bufsize, 2, n, *(SA + k) == (m - 1));
	  }
	}
#else
	buf = SA + m, bufsize = n - (2 * m);
	for(c0 = ALPHABET_SIZE - 2, j = m; 0 < j; --c0) {
	  for(c1 = ALPHABET_SIZE - 1; c0 < c1; j = i, --c1) {
		i = BUCKET_BSTAR(c0, c1);
		if(1 < (j - i)) {
		  sssort(T, PAb, SA + i, SA + j,
				 buf, bufsize, 2, n, *(SA + i) == (m - 1));
		}
	  }
	}
#endif

	/* Compute ranks of type B* substrings. */
	for(i = m - 1; 0 <= i; --i) {
	  if(0 <= SA[i]) {
		j = i;
		do { ISAb[SA[i]] = i; } while((0 <= --i) && (0 <= SA[i]));
		SA[i + 1] = i - j;
		if(i <= 0) { break; }
	  }
	  j = i;
	  do { ISAb[SA[i] = ~SA[i]] = j; } while(SA[--i] < 0);
	  ISAb[SA[i]] = j;
	}

	/* Construct the inverse suffix array of type B* suffixes using trsort. */
	trsort(ISAb, SA, m, 1);

	/* Set the sorted order of tyoe B* suffixes. */
	for(i = n - 1, j = m, c0 = T[n - 1]; 0 <= i;) {
	  for(--i, c1 = c0; (0 <= i) && ((c0 = T[i]) >= c1); --i, c1 = c0) { }
	  if(0 <= i) {
		t = i;
		for(--i, c1 = c0; (0 <= i) && ((c0 = T[i]) <= c1); --i, c1 = c0) { }
		SA[ISAb[--j]] = ((t == 0) || (1 < (t - i))) ? t : ~t;
	  }
	}

	/* Calculate the index of start/end point of each bucket. */
	BUCKET_B(ALPHABET_SIZE - 1, ALPHABET_SIZE - 1) = n; /* end point */
	for(c0 = ALPHABET_SIZE - 2, k = m - 1; 0 <= c0; --c0) {
	  i = BUCKET_A(c0 + 1) - 1;
	  for(c1 = ALPHABET_SIZE - 1; c0 < c1; --c1) {
		t = i - BUCKET_B(c0, c1);
		BUCKET_B(c0, c1) = i; /* end point */

		/* Move all type B* suffixes to the correct position. */
		for(i = t, j = BUCKET_BSTAR(c0, c1);
			j <= k;
			--i, --k) { SA[i] = SA[k]; }
	  }
	  BUCKET_BSTAR(c0, c0 + 1) = i - BUCKET_B(c0, c0) + 1; /* start point */
	  BUCKET_B(c0, c0) = i; /* end point */
	}
  }

  return m;
}

/* Constructs the suffix array by using the sorted order of type B* suffixes. */
static
void
construct_SA(const sauchar_t *T, saidx_t *SA,
			 saidx_t *bucket_A, saidx_t *bucket_B,
			 saidx_t n, saidx_t m) {
  saidx_t *i, *j, *k;
  saidx_t s;
  saint_t c0, c1, c2;

  if(0 < m) {
	/* Construct the sorted order of type B suffixes by using
	   the sorted order of type B* suffixes. */
	for(c1 = ALPHABET_SIZE - 2; 0 <= c1; --c1) {
	  /* Scan the suffix array from right to left. */
	  for(i = SA + BUCKET_BSTAR(c1, c1 + 1),
		  j = SA + BUCKET_A(c1 + 1) - 1, k = NULL, c2 = -1;
		  i <= j;
		  --j) {
		if(0 < (s = *j)) {
		  assert(T[s] == c1);
		  assert(((s + 1) < n) && (T[s] <= T[s + 1]));
		  assert(T[s - 1] <= T[s]);
		  *j = ~s;
		  c0 = T[--s];
		  if((0 < s) && (T[s - 1] > c0)) { s = ~s; }
		  if(c0 != c2) {
			if(0 <= c2) { BUCKET_B(c2, c1) = k - SA; }
			k = SA + BUCKET_B(c2 = c0, c1);
		  }
		  assert(k < j);
		  *k-- = s;
		} else {
		  assert(((s == 0) && (T[s] == c1)) || (s < 0));
		  *j = ~s;
		}
	  }
	}
  }

  /* Construct the suffix array by using
	 the sorted order of type B suffixes. */
  k = SA + BUCKET_A(c2 = T[n - 1]);
  *k++ = (T[n - 2] < c2) ? ~(n - 1) : (n - 1);
  /* Scan the suffix array from left to right. */
  for(i = SA, j = SA + n; i < j; ++i) {
	if(0 < (s = *i)) {
	  assert(T[s - 1] >= T[s]);
	  c0 = T[--s];
	  if((s == 0) || (T[s - 1] < c0)) { s = ~s; }
	  if(c0 != c2) {
		BUCKET_A(c2) = k - SA;
		k = SA + BUCKET_A(c2 = c0);
	  }
	  assert(i < k);
	  *k++ = s;
	} else {
	  assert(s < 0);
	  *i = ~s;
	}
  }
}

/* Constructs the burrows-wheeler transformed string directly
   by using the sorted order of type B* suffixes. */
static
saidx_t
construct_BWT(const sauchar_t *T, saidx_t *SA,
			  saidx_t *bucket_A, saidx_t *bucket_B,
			  saidx_t n, saidx_t m) {
  saidx_t *i, *j, *k, *orig;
  saidx_t s;
  saint_t c0, c1, c2;

  if(0 < m) {
	/* Construct the sorted order of type B suffixes by using
	   the sorted order of type B* suffixes. */
	for(c1 = ALPHABET_SIZE - 2; 0 <= c1; --c1) {
	  /* Scan the suffix array from right to left. */
	  for(i = SA + BUCKET_BSTAR(c1, c1 + 1),
		  j = SA + BUCKET_A(c1 + 1) - 1, k = NULL, c2 = -1;
		  i <= j;
		  --j) {
		if(0 < (s = *j)) {
		  assert(T[s] == c1);
		  assert(((s + 1) < n) && (T[s] <= T[s + 1]));
		  assert(T[s - 1] <= T[s]);
		  c0 = T[--s];
		  *j = ~((saidx_t)c0);
		  if((0 < s) && (T[s - 1] > c0)) { s = ~s; }
		  if(c0 != c2) {
			if(0 <= c2) { BUCKET_B(c2, c1) = k - SA; }
			k = SA + BUCKET_B(c2 = c0, c1);
		  }
		  assert(k < j);
		  *k-- = s;
		} else if(s != 0) {
		  *j = ~s;
#ifndef NDEBUG
		} else {
		  assert(T[s] == c1);
#endif
		}
	  }
	}
  }

  /* Construct the BWTed string by using
	 the sorted order of type B suffixes. */
  k = SA + BUCKET_A(c2 = T[n - 1]);
  *k++ = (T[n - 2] < c2) ? ~((saidx_t)T[n - 2]) : (n - 1);
  /* Scan the suffix array from left to right. */
  for(i = SA, j = SA + n, orig = SA; i < j; ++i) {
	if(0 < (s = *i)) {
	  assert(T[s - 1] >= T[s]);
	  c0 = T[--s];
	  *i = c0;
	  if((0 < s) && (T[s - 1] < c0)) { s = ~((saidx_t)T[s - 1]); }
	  if(c0 != c2) {
		BUCKET_A(c2) = k - SA;
		k = SA + BUCKET_A(c2 = c0);
	  }
	  assert(i < k);
	  *k++ = s;
	} else if(s != 0) {
	  *i = ~s;
	} else {
	  orig = i;
	}
  }

  return orig - SA;
}

/*---------------------------------------------------------------------------*/

/*- Function -*/

saint_t
divsufsort(const sauchar_t *T, saidx_t *SA, saidx_t n) {
  saidx_t *bucket_A, *bucket_B;
  saidx_t m;
  saint_t err = 0;

  /* Check arguments. */
  if((T == NULL) || (SA == NULL) || (n < 0)) { return -1; }
  else if(n == 0) { return 0; }
  else if(n == 1) { SA[0] = 0; return 0; }
  else if(n == 2) { m = (T[0] < T[1]); SA[m ^ 1] = 0, SA[m] = 1; return 0; }

  bucket_A = (saidx_t *)malloc(BUCKET_A_SIZE * sizeof(saidx_t));
  bucket_B = (saidx_t *)malloc(BUCKET_B_SIZE * sizeof(saidx_t));

  /* Suffixsort. */
  if((bucket_A != NULL) && (bucket_B != NULL)) {
	m = sort_typeBstar(T, SA, bucket_A, bucket_B, n);
	construct_SA(T, SA, bucket_A, bucket_B, n, m);
  } else {
	err = -2;
  }

  free(bucket_B);
  free(bucket_A);

  return err;
}

saidx_t
divbwt(const sauchar_t *T, sauchar_t *U, saidx_t *A, saidx_t n) {
  saidx_t *B;
  saidx_t *bucket_A, *bucket_B;
  saidx_t m, pidx, i;

  /* Check arguments. */
  if((T == NULL) || (U == NULL) || (n < 0)) { return -1; }
  else if(n <= 1) { if(n == 1) { U[0] = T[0]; } return n; }

  if((B = A) == NULL) { B = (saidx_t *)malloc((size_t)(n + 1) * sizeof(saidx_t)); }
  bucket_A = (saidx_t *)malloc(BUCKET_A_SIZE * sizeof(saidx_t));
  bucket_B = (saidx_t *)malloc(BUCKET_B_SIZE * sizeof(saidx_t));

  /* Burrows-Wheeler Transform. */
  if((B != NULL) && (bucket_A != NULL) && (bucket_B != NULL)) {
	m = sort_typeBstar(T, B, bucket_A, bucket_B, n);
	pidx = construct_BWT(T, B, bucket_A, bucket_B, n, m);

	/* Copy to output string. */
	U[0] = T[n - 1];
	for(i = 0; i < pidx; ++i) { U[i + 1] = (sauchar_t)B[i]; }
	for(i += 1; i < n; ++i) { U[i] = (sauchar_t)B[i]; }
	pidx += 1;
  } else {
	pidx = -2;
  }

  free(bucket_B);
  free(bucket_A);
  if(A == NULL) { free(B); }

  return pidx;
}

const char *
divsufsort_version(void) {
  return PROJECT_VERSION_FULL;
}

/*** End of inlined file: divsufsort.c ***/


/*** Start of inlined file: sssort.c ***/
//#include "divsufsort_private.h"

/*- Private Functions -*/

static const saint_t lg_table[256]= {
 -1,0,1,1,2,2,2,2,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
  6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7
};

#if (SS_BLOCKSIZE == 0) || (SS_INSERTIONSORT_THRESHOLD < SS_BLOCKSIZE)

static INLINE
saint_t
ss_ilg(saidx_t n) {
#if SS_BLOCKSIZE == 0
# if defined(BUILD_DIVSUFSORT64)
  return (n >> 32) ?
		  ((n >> 48) ?
			((n >> 56) ?
			  56 + lg_table[(n >> 56) & 0xff] :
			  48 + lg_table[(n >> 48) & 0xff]) :
			((n >> 40) ?
			  40 + lg_table[(n >> 40) & 0xff] :
			  32 + lg_table[(n >> 32) & 0xff])) :
		  ((n & 0xffff0000) ?
			((n & 0xff000000) ?
			  24 + lg_table[(n >> 24) & 0xff] :
			  16 + lg_table[(n >> 16) & 0xff]) :
			((n & 0x0000ff00) ?
			   8 + lg_table[(n >>  8) & 0xff] :
			   0 + lg_table[(n >>  0) & 0xff]));
# else
  return (n & 0xffff0000) ?
		  ((n & 0xff000000) ?
			24 + lg_table[(n >> 24) & 0xff] :
			16 + lg_table[(n >> 16) & 0xff]) :
		  ((n & 0x0000ff00) ?
			 8 + lg_table[(n >>  8) & 0xff] :
			 0 + lg_table[(n >>  0) & 0xff]);
# endif
#elif SS_BLOCKSIZE < 256
  return lg_table[n];
#else
  return (n & 0xff00) ?
		  8 + lg_table[(n >> 8) & 0xff] :
		  0 + lg_table[(n >> 0) & 0xff];
#endif
}

#endif /* (SS_BLOCKSIZE == 0) || (SS_INSERTIONSORT_THRESHOLD < SS_BLOCKSIZE) */

#if SS_BLOCKSIZE != 0

static const saint_t sqq_table[256] = {
  0,  16,  22,  27,  32,  35,  39,  42,  45,  48,  50,  53,  55,  57,  59,  61,
 64,  65,  67,  69,  71,  73,  75,  76,  78,  80,  81,  83,  84,  86,  87,  89,
 90,  91,  93,  94,  96,  97,  98,  99, 101, 102, 103, 104, 106, 107, 108, 109,
110, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126,
128, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142,
143, 144, 144, 145, 146, 147, 148, 149, 150, 150, 151, 152, 153, 154, 155, 155,
156, 157, 158, 159, 160, 160, 161, 162, 163, 163, 164, 165, 166, 167, 167, 168,
169, 170, 170, 171, 172, 173, 173, 174, 175, 176, 176, 177, 178, 178, 179, 180,
181, 181, 182, 183, 183, 184, 185, 185, 186, 187, 187, 188, 189, 189, 190, 191,
192, 192, 193, 193, 194, 195, 195, 196, 197, 197, 198, 199, 199, 200, 201, 201,
202, 203, 203, 204, 204, 205, 206, 206, 207, 208, 208, 209, 209, 210, 211, 211,
212, 212, 213, 214, 214, 215, 215, 216, 217, 217, 218, 218, 219, 219, 220, 221,
221, 222, 222, 223, 224, 224, 225, 225, 226, 226, 227, 227, 228, 229, 229, 230,
230, 231, 231, 232, 232, 233, 234, 234, 235, 235, 236, 236, 237, 237, 238, 238,
239, 240, 240, 241, 241, 242, 242, 243, 243, 244, 244, 245, 245, 246, 246, 247,
247, 248, 248, 249, 249, 250, 250, 251, 251, 252, 252, 253, 253, 254, 254, 255
};

static INLINE
saidx_t
ss_isqrt(saidx_t x) {
  saidx_t y, e;

  if(x >= (SS_BLOCKSIZE * SS_BLOCKSIZE)) { return SS_BLOCKSIZE; }
  e = (x & 0xffff0000) ?
		((x & 0xff000000) ?
		  24 + lg_table[(x >> 24) & 0xff] :
		  16 + lg_table[(x >> 16) & 0xff]) :
		((x & 0x0000ff00) ?
		   8 + lg_table[(x >>  8) & 0xff] :
		   0 + lg_table[(x >>  0) & 0xff]);

  if(e >= 16) {
	y = sqq_table[x >> ((e - 6) - (e & 1))] << ((e >> 1) - 7);
	if(e >= 24) { y = (y + 1 + x / y) >> 1; }
	y = (y + 1 + x / y) >> 1;
  } else if(e >= 8) {
	y = (sqq_table[x >> ((e - 6) - (e & 1))] >> (7 - (e >> 1))) + 1;
  } else {
	return sqq_table[x] >> 4;
  }

  return (x < (y * y)) ? y - 1 : y;
}

#endif /* SS_BLOCKSIZE != 0 */

/*---------------------------------------------------------------------------*/

/* Compares two suffixes. */
static INLINE
saint_t
ss_compare(const sauchar_t *T,
		   const saidx_t *p1, const saidx_t *p2,
		   saidx_t depth) {
  const sauchar_t *U1, *U2, *U1n, *U2n;

  for(U1 = T + depth + *p1,
	  U2 = T + depth + *p2,
	  U1n = T + *(p1 + 1) + 2,
	  U2n = T + *(p2 + 1) + 2;
	  (U1 < U1n) && (U2 < U2n) && (*U1 == *U2);
	  ++U1, ++U2) {
  }

  return U1 < U1n ?
		(U2 < U2n ? *U1 - *U2 : 1) :
		(U2 < U2n ? -1 : 0);
}

/*---------------------------------------------------------------------------*/

#if (SS_BLOCKSIZE != 1) && (SS_INSERTIONSORT_THRESHOLD != 1)

/* Insertionsort for small size groups */
static
void
ss_insertionsort(const sauchar_t *T, const saidx_t *PA,
				 saidx_t *first, saidx_t *last, saidx_t depth) {
  saidx_t *i, *j;
  saidx_t t;
  saint_t r;

  for(i = last - 2; first <= i; --i) {
	for(t = *i, j = i + 1; 0 < (r = ss_compare(T, PA + t, PA + *j, depth));) {
	  do { *(j - 1) = *j; } while((++j < last) && (*j < 0));
	  if(last <= j) { break; }
	}
	if(r == 0) { *j = ~*j; }
	*(j - 1) = t;
  }
}

#endif /* (SS_BLOCKSIZE != 1) && (SS_INSERTIONSORT_THRESHOLD != 1) */

/*---------------------------------------------------------------------------*/

#if (SS_BLOCKSIZE == 0) || (SS_INSERTIONSORT_THRESHOLD < SS_BLOCKSIZE)

static INLINE
void
ss_fixdown(const sauchar_t *Td, const saidx_t *PA,
		   saidx_t *SA, saidx_t i, saidx_t size) {
  saidx_t j, k;
  saidx_t v;
  saint_t c, d, e;

  for(v = SA[i], c = Td[PA[v]]; (j = 2 * i + 1) < size; SA[i] = SA[k], i = k) {
	d = Td[PA[SA[k = j++]]];
	if(d < (e = Td[PA[SA[j]]])) { k = j; d = e; }
	if(d <= c) { break; }
  }
  SA[i] = v;
}

/* Simple top-down heapsort. */
static
void
ss_heapsort(const sauchar_t *Td, const saidx_t *PA, saidx_t *SA, saidx_t size) {
  saidx_t i, m;
  saidx_t t;

  m = size;
  if((size % 2) == 0) {
	m--;
	if(Td[PA[SA[m / 2]]] < Td[PA[SA[m]]]) { SWAP(SA[m], SA[m / 2]); }
  }

  for(i = m / 2 - 1; 0 <= i; --i) { ss_fixdown(Td, PA, SA, i, m); }
  if((size % 2) == 0) { SWAP(SA[0], SA[m]); ss_fixdown(Td, PA, SA, 0, m); }
  for(i = m - 1; 0 < i; --i) {
	t = SA[0], SA[0] = SA[i];
	ss_fixdown(Td, PA, SA, 0, i);
	SA[i] = t;
  }
}

/*---------------------------------------------------------------------------*/

/* Returns the median of three elements. */
static INLINE
saidx_t *
ss_median3(const sauchar_t *Td, const saidx_t *PA,
		   saidx_t *v1, saidx_t *v2, saidx_t *v3) {
  saidx_t *t;
  if(Td[PA[*v1]] > Td[PA[*v2]]) { SWAP(v1, v2); }
  if(Td[PA[*v2]] > Td[PA[*v3]]) {
	if(Td[PA[*v1]] > Td[PA[*v3]]) { return v1; }
	else { return v3; }
  }
  return v2;
}

/* Returns the median of five elements. */
static INLINE
saidx_t *
ss_median5(const sauchar_t *Td, const saidx_t *PA,
		   saidx_t *v1, saidx_t *v2, saidx_t *v3, saidx_t *v4, saidx_t *v5) {
  saidx_t *t;
  if(Td[PA[*v2]] > Td[PA[*v3]]) { SWAP(v2, v3); }
  if(Td[PA[*v4]] > Td[PA[*v5]]) { SWAP(v4, v5); }
  if(Td[PA[*v2]] > Td[PA[*v4]]) { SWAP(v2, v4); SWAP(v3, v5); }
  if(Td[PA[*v1]] > Td[PA[*v3]]) { SWAP(v1, v3); }
  if(Td[PA[*v1]] > Td[PA[*v4]]) { SWAP(v1, v4); SWAP(v3, v5); }
  if(Td[PA[*v3]] > Td[PA[*v4]]) { return v4; }
  return v3;
}

/* Returns the pivot element. */
static INLINE
saidx_t *
ss_pivot(const sauchar_t *Td, const saidx_t *PA, saidx_t *first, saidx_t *last) {
  saidx_t *middle;
  saidx_t t;

  t = last - first;
  middle = first + t / 2;

  if(t <= 512) {
	if(t <= 32) {
	  return ss_median3(Td, PA, first, middle, last - 1);
	} else {
	  t >>= 2;
	  return ss_median5(Td, PA, first, first + t, middle, last - 1 - t, last - 1);
	}
  }
  t >>= 3;
  first  = ss_median3(Td, PA, first, first + t, first + (t << 1));
  middle = ss_median3(Td, PA, middle - t, middle, middle + t);
  last   = ss_median3(Td, PA, last - 1 - (t << 1), last - 1 - t, last - 1);
  return ss_median3(Td, PA, first, middle, last);
}

/*---------------------------------------------------------------------------*/

/* Binary partition for substrings. */
static INLINE
saidx_t *
ss_partition(const saidx_t *PA,
					saidx_t *first, saidx_t *last, saidx_t depth) {
  saidx_t *a, *b;
  saidx_t t;
  for(a = first - 1, b = last;;) {
	for(; (++a < b) && ((PA[*a] + depth) >= (PA[*a + 1] + 1));) { *a = ~*a; }
	for(; (a < --b) && ((PA[*b] + depth) <  (PA[*b + 1] + 1));) { }
	if(b <= a) { break; }
	t = ~*b;
	*b = *a;
	*a = t;
  }
  if(first < a) { *first = ~*first; }
  return a;
}

/* Multikey introsort for medium size groups. */
static
void
ss_mintrosort(const sauchar_t *T, const saidx_t *PA,
			  saidx_t *first, saidx_t *last,
			  saidx_t depth) {
#define STACK_SIZE SS_MISORT_STACKSIZE
  struct { saidx_t *a, *b, c; saint_t d; } stack[STACK_SIZE];
  const sauchar_t *Td;
  saidx_t *a, *b, *c, *d, *e, *f;
  saidx_t s, t;
  saint_t ssize;
  saint_t limit;
  saint_t v, x = 0;

  for(ssize = 0, limit = ss_ilg(last - first);;) {

	if((last - first) <= SS_INSERTIONSORT_THRESHOLD) {
#if 1 < SS_INSERTIONSORT_THRESHOLD
	  if(1 < (last - first)) { ss_insertionsort(T, PA, first, last, depth); }
#endif
	  STACK_POP(first, last, depth, limit);
	  continue;
	}

	Td = T + depth;
	if(limit-- == 0) { ss_heapsort(Td, PA, first, last - first); }
	if(limit < 0) {
	  for(a = first + 1, v = Td[PA[*first]]; a < last; ++a) {
		if((x = Td[PA[*a]]) != v) {
		  if(1 < (a - first)) { break; }
		  v = x;
		  first = a;
		}
	  }
	  if(Td[PA[*first] - 1] < v) {
		first = ss_partition(PA, first, a, depth);
	  }
	  if((a - first) <= (last - a)) {
		if(1 < (a - first)) {
		  STACK_PUSH(a, last, depth, -1);
		  last = a, depth += 1, limit = ss_ilg(a - first);
		} else {
		  first = a, limit = -1;
		}
	  } else {
		if(1 < (last - a)) {
		  STACK_PUSH(first, a, depth + 1, ss_ilg(a - first));
		  first = a, limit = -1;
		} else {
		  last = a, depth += 1, limit = ss_ilg(a - first);
		}
	  }
	  continue;
	}

	/* choose pivot */
	a = ss_pivot(Td, PA, first, last);
	v = Td[PA[*a]];
	SWAP(*first, *a);

	/* partition */
	for(b = first; (++b < last) && ((x = Td[PA[*b]]) == v);) { }
	if(((a = b) < last) && (x < v)) {
	  for(; (++b < last) && ((x = Td[PA[*b]]) <= v);) {
		if(x == v) { SWAP(*b, *a); ++a; }
	  }
	}
	for(c = last; (b < --c) && ((x = Td[PA[*c]]) == v);) { }
	if((b < (d = c)) && (x > v)) {
	  for(; (b < --c) && ((x = Td[PA[*c]]) >= v);) {
		if(x == v) { SWAP(*c, *d); --d; }
	  }
	}
	for(; b < c;) {
	  SWAP(*b, *c);
	  for(; (++b < c) && ((x = Td[PA[*b]]) <= v);) {
		if(x == v) { SWAP(*b, *a); ++a; }
	  }
	  for(; (b < --c) && ((x = Td[PA[*c]]) >= v);) {
		if(x == v) { SWAP(*c, *d); --d; }
	  }
	}

	if(a <= d) {
	  c = b - 1;

	  if((s = a - first) > (t = b - a)) { s = t; }
	  for(e = first, f = b - s; 0 < s; --s, ++e, ++f) { SWAP(*e, *f); }
	  if((s = d - c) > (t = last - d - 1)) { s = t; }
	  for(e = b, f = last - s; 0 < s; --s, ++e, ++f) { SWAP(*e, *f); }

	  a = first + (b - a), c = last - (d - c);
	  b = (v <= Td[PA[*a] - 1]) ? a : ss_partition(PA, a, c, depth);

	  if((a - first) <= (last - c)) {
		if((last - c) <= (c - b)) {
		  STACK_PUSH(b, c, depth + 1, ss_ilg(c - b));
		  STACK_PUSH(c, last, depth, limit);
		  last = a;
		} else if((a - first) <= (c - b)) {
		  STACK_PUSH(c, last, depth, limit);
		  STACK_PUSH(b, c, depth + 1, ss_ilg(c - b));
		  last = a;
		} else {
		  STACK_PUSH(c, last, depth, limit);
		  STACK_PUSH(first, a, depth, limit);
		  first = b, last = c, depth += 1, limit = ss_ilg(c - b);
		}
	  } else {
		if((a - first) <= (c - b)) {
		  STACK_PUSH(b, c, depth + 1, ss_ilg(c - b));
		  STACK_PUSH(first, a, depth, limit);
		  first = c;
		} else if((last - c) <= (c - b)) {
		  STACK_PUSH(first, a, depth, limit);
		  STACK_PUSH(b, c, depth + 1, ss_ilg(c - b));
		  first = c;
		} else {
		  STACK_PUSH(first, a, depth, limit);
		  STACK_PUSH(c, last, depth, limit);
		  first = b, last = c, depth += 1, limit = ss_ilg(c - b);
		}
	  }
	} else {
	  limit += 1;
	  if(Td[PA[*first] - 1] < v) {
		first = ss_partition(PA, first, last, depth);
		limit = ss_ilg(last - first);
	  }
	  depth += 1;
	}
  }
#undef STACK_SIZE
}

#endif /* (SS_BLOCKSIZE == 0) || (SS_INSERTIONSORT_THRESHOLD < SS_BLOCKSIZE) */

/*---------------------------------------------------------------------------*/

#if SS_BLOCKSIZE != 0

static INLINE
void
ss_blockswap(saidx_t *a, saidx_t *b, saidx_t n) {
  saidx_t t;
  for(; 0 < n; --n, ++a, ++b) {
	t = *a, *a = *b, *b = t;
  }
}

static INLINE
void
ss_rotate(saidx_t *first, saidx_t *middle, saidx_t *last) {
  saidx_t *a, *b, t;
  saidx_t l, r;
  l = middle - first, r = last - middle;
  for(; (0 < l) && (0 < r);) {
	if(l == r) { ss_blockswap(first, middle, l); break; }
	if(l < r) {
	  a = last - 1, b = middle - 1;
	  t = *a;
	  do {
		*a-- = *b, *b-- = *a;
		if(b < first) {
		  *a = t;
		  last = a;
		  if((r -= l + 1) <= l) { break; }
		  a -= 1, b = middle - 1;
		  t = *a;
		}
	  } while(1);
	} else {
	  a = first, b = middle;
	  t = *a;
	  do {
		*a++ = *b, *b++ = *a;
		if(last <= b) {
		  *a = t;
		  first = a + 1;
		  if((l -= r + 1) <= r) { break; }
		  a += 1, b = middle;
		  t = *a;
		}
	  } while(1);
	}
  }
}

/*---------------------------------------------------------------------------*/

static
void
ss_inplacemerge(const sauchar_t *T, const saidx_t *PA,
				saidx_t *first, saidx_t *middle, saidx_t *last,
				saidx_t depth) {
  const saidx_t *p;
  saidx_t *a, *b;
  saidx_t len, half;
  saint_t q, r;
  saint_t x;

  for(;;) {
	if(*(last - 1) < 0) { x = 1; p = PA + ~*(last - 1); }
	else                { x = 0; p = PA +  *(last - 1); }
	for(a = first, len = middle - first, half = len >> 1, r = -1;
		0 < len;
		len = half, half >>= 1) {
	  b = a + half;
	  q = ss_compare(T, PA + ((0 <= *b) ? *b : ~*b), p, depth);
	  if(q < 0) {
		a = b + 1;
		half -= (len & 1) ^ 1;
	  } else {
		r = q;
	  }
	}
	if(a < middle) {
	  if(r == 0) { *a = ~*a; }
	  ss_rotate(a, middle, last);
	  last -= middle - a;
	  middle = a;
	  if(first == middle) { break; }
	}
	--last;
	if(x != 0) { while(*--last < 0) { } }
	if(middle == last) { break; }
  }
}

/*---------------------------------------------------------------------------*/

/* Merge-forward with internal buffer. */
static
void
ss_mergeforward(const sauchar_t *T, const saidx_t *PA,
				saidx_t *first, saidx_t *middle, saidx_t *last,
				saidx_t *buf, saidx_t depth) {
  saidx_t *a, *b, *c, *bufend;
  saidx_t t;
  saint_t r;

  bufend = buf + (middle - first) - 1;
  ss_blockswap(buf, first, middle - first);

  for(t = *(a = first), b = buf, c = middle;;) {
	r = ss_compare(T, PA + *b, PA + *c, depth);
	if(r < 0) {
	  do {
		*a++ = *b;
		if(bufend <= b) { *bufend = t; return; }
		*b++ = *a;
	  } while(*b < 0);
	} else if(r > 0) {
	  do {
		*a++ = *c, *c++ = *a;
		if(last <= c) {
		  while(b < bufend) { *a++ = *b, *b++ = *a; }
		  *a = *b, *b = t;
		  return;
		}
	  } while(*c < 0);
	} else {
	  *c = ~*c;
	  do {
		*a++ = *b;
		if(bufend <= b) { *bufend = t; return; }
		*b++ = *a;
	  } while(*b < 0);

	  do {
		*a++ = *c, *c++ = *a;
		if(last <= c) {
		  while(b < bufend) { *a++ = *b, *b++ = *a; }
		  *a = *b, *b = t;
		  return;
		}
	  } while(*c < 0);
	}
  }
}

/* Merge-backward with internal buffer. */
static
void
ss_mergebackward(const sauchar_t *T, const saidx_t *PA,
				 saidx_t *first, saidx_t *middle, saidx_t *last,
				 saidx_t *buf, saidx_t depth) {
  const saidx_t *p1, *p2;
  saidx_t *a, *b, *c, *bufend;
  saidx_t t;
  saint_t r;
  saint_t x;

  bufend = buf + (last - middle) - 1;
  ss_blockswap(buf, middle, last - middle);

  x = 0;
  if(*bufend < 0)       { p1 = PA + ~*bufend; x |= 1; }
  else                  { p1 = PA +  *bufend; }
  if(*(middle - 1) < 0) { p2 = PA + ~*(middle - 1); x |= 2; }
  else                  { p2 = PA +  *(middle - 1); }
  for(t = *(a = last - 1), b = bufend, c = middle - 1;;) {
	r = ss_compare(T, p1, p2, depth);
	if(0 < r) {
	  if(x & 1) { do { *a-- = *b, *b-- = *a; } while(*b < 0); x ^= 1; }
	  *a-- = *b;
	  if(b <= buf) { *buf = t; break; }
	  *b-- = *a;
	  if(*b < 0) { p1 = PA + ~*b; x |= 1; }
	  else       { p1 = PA +  *b; }
	} else if(r < 0) {
	  if(x & 2) { do { *a-- = *c, *c-- = *a; } while(*c < 0); x ^= 2; }
	  *a-- = *c, *c-- = *a;
	  if(c < first) {
		while(buf < b) { *a-- = *b, *b-- = *a; }
		*a = *b, *b = t;
		break;
	  }
	  if(*c < 0) { p2 = PA + ~*c; x |= 2; }
	  else       { p2 = PA +  *c; }
	} else {
	  if(x & 1) { do { *a-- = *b, *b-- = *a; } while(*b < 0); x ^= 1; }
	  *a-- = ~*b;
	  if(b <= buf) { *buf = t; break; }
	  *b-- = *a;
	  if(x & 2) { do { *a-- = *c, *c-- = *a; } while(*c < 0); x ^= 2; }
	  *a-- = *c, *c-- = *a;
	  if(c < first) {
		while(buf < b) { *a-- = *b, *b-- = *a; }
		*a = *b, *b = t;
		break;
	  }
	  if(*b < 0) { p1 = PA + ~*b; x |= 1; }
	  else       { p1 = PA +  *b; }
	  if(*c < 0) { p2 = PA + ~*c; x |= 2; }
	  else       { p2 = PA +  *c; }
	}
  }
}

/* D&C based merge. */
static
void
ss_swapmerge(const sauchar_t *T, const saidx_t *PA,
			 saidx_t *first, saidx_t *middle, saidx_t *last,
			 saidx_t *buf, saidx_t bufsize, saidx_t depth) {
#define STACK_SIZE SS_SMERGE_STACKSIZE
#define GETIDX(a) ((0 <= (a)) ? (a) : (~(a)))
#define MERGE_CHECK(a, b, c)\
  do {\
	if(((c) & 1) ||\
	   (((c) & 2) && (ss_compare(T, PA + GETIDX(*((a) - 1)), PA + *(a), depth) == 0))) {\
	  *(a) = ~*(a);\
	}\
	if(((c) & 4) && ((ss_compare(T, PA + GETIDX(*((b) - 1)), PA + *(b), depth) == 0))) {\
	  *(b) = ~*(b);\
	}\
  } while(0)
  struct { saidx_t *a, *b, *c; saint_t d; } stack[STACK_SIZE];
  saidx_t *l, *r, *lm, *rm;
  saidx_t m, len, half;
  saint_t ssize;
  saint_t check, next;

  for(check = 0, ssize = 0;;) {
	if((last - middle) <= bufsize) {
	  if((first < middle) && (middle < last)) {
		ss_mergebackward(T, PA, first, middle, last, buf, depth);
	  }
	  MERGE_CHECK(first, last, check);
	  STACK_POP(first, middle, last, check);
	  continue;
	}

	if((middle - first) <= bufsize) {
	  if(first < middle) {
		ss_mergeforward(T, PA, first, middle, last, buf, depth);
	  }
	  MERGE_CHECK(first, last, check);
	  STACK_POP(first, middle, last, check);
	  continue;
	}

	for(m = 0, len = MIN(middle - first, last - middle), half = len >> 1;
		0 < len;
		len = half, half >>= 1) {
	  if(ss_compare(T, PA + GETIDX(*(middle + m + half)),
					   PA + GETIDX(*(middle - m - half - 1)), depth) < 0) {
		m += half + 1;
		half -= (len & 1) ^ 1;
	  }
	}

	if(0 < m) {
	  lm = middle - m, rm = middle + m;
	  ss_blockswap(lm, middle, m);
	  l = r = middle, next = 0;
	  if(rm < last) {
		if(*rm < 0) {
		  *rm = ~*rm;
		  if(first < lm) { for(; *--l < 0;) { } next |= 4; }
		  next |= 1;
		} else if(first < lm) {
		  for(; *r < 0; ++r) { }
		  next |= 2;
		}
	  }

	  if((l - first) <= (last - r)) {
		STACK_PUSH(r, rm, last, (next & 3) | (check & 4));
		middle = lm, last = l, check = (check & 3) | (next & 4);
	  } else {
		if((next & 2) && (r == middle)) { next ^= 6; }
		STACK_PUSH(first, lm, l, (check & 3) | (next & 4));
		first = r, middle = rm, check = (next & 3) | (check & 4);
	  }
	} else {
	  if(ss_compare(T, PA + GETIDX(*(middle - 1)), PA + *middle, depth) == 0) {
		*middle = ~*middle;
	  }
	  MERGE_CHECK(first, last, check);
	  STACK_POP(first, middle, last, check);
	}
  }
#undef STACK_SIZE
}

#endif /* SS_BLOCKSIZE != 0 */

/*---------------------------------------------------------------------------*/

/*- Function -*/

/* Substring sort */
void
sssort(const sauchar_t *T, const saidx_t *PA,
	   saidx_t *first, saidx_t *last,
	   saidx_t *buf, saidx_t bufsize,
	   saidx_t depth, saidx_t n, saint_t lastsuffix) {
  saidx_t *a;
#if SS_BLOCKSIZE != 0
  saidx_t *b, *middle, *curbuf;
  saidx_t j, k, curbufsize, limit;
#endif
  saidx_t i;

  if(lastsuffix != 0) { ++first; }

#if SS_BLOCKSIZE == 0
  ss_mintrosort(T, PA, first, last, depth);
#else
  if((bufsize < SS_BLOCKSIZE) &&
	  (bufsize < (last - first)) &&
	  (bufsize < (limit = ss_isqrt(last - first)))) {
	if(SS_BLOCKSIZE < limit) { limit = SS_BLOCKSIZE; }
	buf = middle = last - limit, bufsize = limit;
  } else {
	middle = last, limit = 0;
  }
  for(a = first, i = 0; SS_BLOCKSIZE < (middle - a); a += SS_BLOCKSIZE, ++i) {
#if SS_INSERTIONSORT_THRESHOLD < SS_BLOCKSIZE
	ss_mintrosort(T, PA, a, a + SS_BLOCKSIZE, depth);
#elif 1 < SS_BLOCKSIZE
	ss_insertionsort(T, PA, a, a + SS_BLOCKSIZE, depth);
#endif
	curbufsize = last - (a + SS_BLOCKSIZE);
	curbuf = a + SS_BLOCKSIZE;
	if(curbufsize <= bufsize) { curbufsize = bufsize, curbuf = buf; }
	for(b = a, k = SS_BLOCKSIZE, j = i; j & 1; b -= k, k <<= 1, j >>= 1) {
	  ss_swapmerge(T, PA, b - k, b, b + k, curbuf, curbufsize, depth);
	}
  }
#if SS_INSERTIONSORT_THRESHOLD < SS_BLOCKSIZE
  ss_mintrosort(T, PA, a, middle, depth);
#elif 1 < SS_BLOCKSIZE
  ss_insertionsort(T, PA, a, middle, depth);
#endif
  for(k = SS_BLOCKSIZE; i != 0; k <<= 1, i >>= 1) {
	if(i & 1) {
	  ss_swapmerge(T, PA, a - k, a, middle, buf, bufsize, depth);
	  a -= k;
	}
  }
  if(limit != 0) {
#if SS_INSERTIONSORT_THRESHOLD < SS_BLOCKSIZE
	ss_mintrosort(T, PA, middle, last, depth);
#elif 1 < SS_BLOCKSIZE
	ss_insertionsort(T, PA, middle, last, depth);
#endif
	ss_inplacemerge(T, PA, first, middle, last, depth);
  }
#endif

  if(lastsuffix != 0) {
	/* Insert last type B* suffix. */
	saidx_t PAi[2]; PAi[0] = PA[*(first - 1)], PAi[1] = n - 2;
	for(a = first, i = *(first - 1);
		(a < last) && ((*a < 0) || (0 < ss_compare(T, &(PAi[0]), PA + *a, depth)));
		++a) {
	  *(a - 1) = *a;
	}
	*(a - 1) = i;
  }
}

/*** End of inlined file: sssort.c ***/

#define lg_table lg_table2

/*** Start of inlined file: trsort.c ***/
//#include "divsufsort_private.h"

/*- Private Functions -*/

static const saint_t lg_table[256]= {
 -1,0,1,1,2,2,2,2,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
  6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7
};

static INLINE
saint_t
tr_ilg(saidx_t n) {
#if defined(BUILD_DIVSUFSORT64)
  return (n >> 32) ?
		  ((n >> 48) ?
			((n >> 56) ?
			  56 + lg_table[(n >> 56) & 0xff] :
			  48 + lg_table[(n >> 48) & 0xff]) :
			((n >> 40) ?
			  40 + lg_table[(n >> 40) & 0xff] :
			  32 + lg_table[(n >> 32) & 0xff])) :
		  ((n & 0xffff0000) ?
			((n & 0xff000000) ?
			  24 + lg_table[(n >> 24) & 0xff] :
			  16 + lg_table[(n >> 16) & 0xff]) :
			((n & 0x0000ff00) ?
			   8 + lg_table[(n >>  8) & 0xff] :
			   0 + lg_table[(n >>  0) & 0xff]));
#else
  return (n & 0xffff0000) ?
		  ((n & 0xff000000) ?
			24 + lg_table[(n >> 24) & 0xff] :
			16 + lg_table[(n >> 16) & 0xff]) :
		  ((n & 0x0000ff00) ?
			 8 + lg_table[(n >>  8) & 0xff] :
			 0 + lg_table[(n >>  0) & 0xff]);
#endif
}

/*---------------------------------------------------------------------------*/

/* Simple insertionsort for small size groups. */
static
void
tr_insertionsort(const saidx_t *ISAd, saidx_t *first, saidx_t *last) {
  saidx_t *a, *b;
  saidx_t t, r;

  for(a = first + 1; a < last; ++a) {
	for(t = *a, b = a - 1; 0 > (r = ISAd[t] - ISAd[*b]);) {
	  do { *(b + 1) = *b; } while((first <= --b) && (*b < 0));
	  if(b < first) { break; }
	}
	if(r == 0) { *b = ~*b; }
	*(b + 1) = t;
  }
}

/*---------------------------------------------------------------------------*/

static INLINE
void
tr_fixdown(const saidx_t *ISAd, saidx_t *SA, saidx_t i, saidx_t size) {
  saidx_t j, k;
  saidx_t v;
  saidx_t c, d, e;

  for(v = SA[i], c = ISAd[v]; (j = 2 * i + 1) < size; SA[i] = SA[k], i = k) {
	d = ISAd[SA[k = j++]];
	if(d < (e = ISAd[SA[j]])) { k = j; d = e; }
	if(d <= c) { break; }
  }
  SA[i] = v;
}

/* Simple top-down heapsort. */
static
void
tr_heapsort(const saidx_t *ISAd, saidx_t *SA, saidx_t size) {
  saidx_t i, m;
  saidx_t t;

  m = size;
  if((size % 2) == 0) {
	m--;
	if(ISAd[SA[m / 2]] < ISAd[SA[m]]) { SWAP(SA[m], SA[m / 2]); }
  }

  for(i = m / 2 - 1; 0 <= i; --i) { tr_fixdown(ISAd, SA, i, m); }
  if((size % 2) == 0) { SWAP(SA[0], SA[m]); tr_fixdown(ISAd, SA, 0, m); }
  for(i = m - 1; 0 < i; --i) {
	t = SA[0], SA[0] = SA[i];
	tr_fixdown(ISAd, SA, 0, i);
	SA[i] = t;
  }
}

/*---------------------------------------------------------------------------*/

/* Returns the median of three elements. */
static INLINE
saidx_t *
tr_median3(const saidx_t *ISAd, saidx_t *v1, saidx_t *v2, saidx_t *v3) {
  saidx_t *t;
  if(ISAd[*v1] > ISAd[*v2]) { SWAP(v1, v2); }
  if(ISAd[*v2] > ISAd[*v3]) {
	if(ISAd[*v1] > ISAd[*v3]) { return v1; }
	else { return v3; }
  }
  return v2;
}

/* Returns the median of five elements. */
static INLINE
saidx_t *
tr_median5(const saidx_t *ISAd,
		   saidx_t *v1, saidx_t *v2, saidx_t *v3, saidx_t *v4, saidx_t *v5) {
  saidx_t *t;
  if(ISAd[*v2] > ISAd[*v3]) { SWAP(v2, v3); }
  if(ISAd[*v4] > ISAd[*v5]) { SWAP(v4, v5); }
  if(ISAd[*v2] > ISAd[*v4]) { SWAP(v2, v4); SWAP(v3, v5); }
  if(ISAd[*v1] > ISAd[*v3]) { SWAP(v1, v3); }
  if(ISAd[*v1] > ISAd[*v4]) { SWAP(v1, v4); SWAP(v3, v5); }
  if(ISAd[*v3] > ISAd[*v4]) { return v4; }
  return v3;
}

/* Returns the pivot element. */
static INLINE
saidx_t *
tr_pivot(const saidx_t *ISAd, saidx_t *first, saidx_t *last) {
  saidx_t *middle;
  saidx_t t;

  t = last - first;
  middle = first + t / 2;

  if(t <= 512) {
	if(t <= 32) {
	  return tr_median3(ISAd, first, middle, last - 1);
	} else {
	  t >>= 2;
	  return tr_median5(ISAd, first, first + t, middle, last - 1 - t, last - 1);
	}
  }
  t >>= 3;
  first  = tr_median3(ISAd, first, first + t, first + (t << 1));
  middle = tr_median3(ISAd, middle - t, middle, middle + t);
  last   = tr_median3(ISAd, last - 1 - (t << 1), last - 1 - t, last - 1);
  return tr_median3(ISAd, first, middle, last);
}

/*---------------------------------------------------------------------------*/

typedef struct _trbudget_t trbudget_t;
struct _trbudget_t {
  saidx_t chance;
  saidx_t remain;
  saidx_t incval;
  saidx_t count;
};

static INLINE
void
trbudget_init(trbudget_t *budget, saidx_t chance, saidx_t incval) {
  budget->chance = chance;
  budget->remain = budget->incval = incval;
}

static INLINE
saint_t
trbudget_check(trbudget_t *budget, saidx_t size) {
  if(size <= budget->remain) { budget->remain -= size; return 1; }
  if(budget->chance == 0) { budget->count += size; return 0; }
  budget->remain += budget->incval - size;
  budget->chance -= 1;
  return 1;
}

/*---------------------------------------------------------------------------*/

static INLINE
void
tr_partition(const saidx_t *ISAd,
			 saidx_t *first, saidx_t *middle, saidx_t *last,
			 saidx_t **pa, saidx_t **pb, saidx_t v) {
  saidx_t *a, *b, *c, *d, *e, *f;
  saidx_t t, s;
  saidx_t x = 0;

  for(b = middle - 1; (++b < last) && ((x = ISAd[*b]) == v);) { }
  if(((a = b) < last) && (x < v)) {
	for(; (++b < last) && ((x = ISAd[*b]) <= v);) {
	  if(x == v) { SWAP(*b, *a); ++a; }
	}
  }
  for(c = last; (b < --c) && ((x = ISAd[*c]) == v);) { }
  if((b < (d = c)) && (x > v)) {
	for(; (b < --c) && ((x = ISAd[*c]) >= v);) {
	  if(x == v) { SWAP(*c, *d); --d; }
	}
  }
  for(; b < c;) {
	SWAP(*b, *c);
	for(; (++b < c) && ((x = ISAd[*b]) <= v);) {
	  if(x == v) { SWAP(*b, *a); ++a; }
	}
	for(; (b < --c) && ((x = ISAd[*c]) >= v);) {
	  if(x == v) { SWAP(*c, *d); --d; }
	}
  }

  if(a <= d) {
	c = b - 1;
	if((s = a - first) > (t = b - a)) { s = t; }
	for(e = first, f = b - s; 0 < s; --s, ++e, ++f) { SWAP(*e, *f); }
	if((s = d - c) > (t = last - d - 1)) { s = t; }
	for(e = b, f = last - s; 0 < s; --s, ++e, ++f) { SWAP(*e, *f); }
	first += (b - a), last -= (d - c);
  }
  *pa = first, *pb = last;
}

static
void
tr_copy(saidx_t *ISA, const saidx_t *SA,
		saidx_t *first, saidx_t *a, saidx_t *b, saidx_t *last,
		saidx_t depth) {
  /* sort suffixes of middle partition
	 by using sorted order of suffixes of left and right partition. */
  saidx_t *c, *d, *e;
  saidx_t s, v;

  v = b - SA - 1;
  for(c = first, d = a - 1; c <= d; ++c) {
	if((0 <= (s = *c - depth)) && (ISA[s] == v)) {
	  *++d = s;
	  ISA[s] = d - SA;
	}
  }
  for(c = last - 1, e = d + 1, d = b; e < d; --c) {
	if((0 <= (s = *c - depth)) && (ISA[s] == v)) {
	  *--d = s;
	  ISA[s] = d - SA;
	}
  }
}

static
void
tr_partialcopy(saidx_t *ISA, const saidx_t *SA,
			   saidx_t *first, saidx_t *a, saidx_t *b, saidx_t *last,
			   saidx_t depth) {
  saidx_t *c, *d, *e;
  saidx_t s, v;
  saidx_t rank, lastrank, newrank = -1;

  v = b - SA - 1;
  lastrank = -1;
  for(c = first, d = a - 1; c <= d; ++c) {
	if((0 <= (s = *c - depth)) && (ISA[s] == v)) {
	  *++d = s;
	  rank = ISA[s + depth];
	  if(lastrank != rank) { lastrank = rank; newrank = d - SA; }
	  ISA[s] = newrank;
	}
  }

  lastrank = -1;
  for(e = d; first <= e; --e) {
	rank = ISA[*e];
	if(lastrank != rank) { lastrank = rank; newrank = e - SA; }
	if(newrank != rank) { ISA[*e] = newrank; }
  }

  lastrank = -1;
  for(c = last - 1, e = d + 1, d = b; e < d; --c) {
	if((0 <= (s = *c - depth)) && (ISA[s] == v)) {
	  *--d = s;
	  rank = ISA[s + depth];
	  if(lastrank != rank) { lastrank = rank; newrank = d - SA; }
	  ISA[s] = newrank;
	}
  }
}

static
void
tr_introsort(saidx_t *ISA, const saidx_t *ISAd,
			 saidx_t *SA, saidx_t *first, saidx_t *last,
			 trbudget_t *budget) {
#define STACK_SIZE TR_STACKSIZE
  struct { const saidx_t *a; saidx_t *b, *c; saint_t d, e; }stack[STACK_SIZE];
  saidx_t *a, *b, *c;
  saidx_t t;
  saidx_t v, x = 0;
  saidx_t incr = ISAd - ISA;
  saint_t limit, next;
  saint_t ssize, trlink = -1;

  for(ssize = 0, limit = tr_ilg(last - first);;) {

	if(limit < 0) {
	  if(limit == -1) {
		/* tandem repeat partition */
		tr_partition(ISAd - incr, first, first, last, &a, &b, last - SA - 1);

		/* update ranks */
		if(a < last) {
		  for(c = first, v = a - SA - 1; c < a; ++c) { ISA[*c] = v; }
		}
		if(b < last) {
		  for(c = a, v = b - SA - 1; c < b; ++c) { ISA[*c] = v; }
		}

		/* push */
		if(1 < (b - a)) {
		  STACK_PUSH5(NULL, a, b, 0, 0);
		  STACK_PUSH5(ISAd - incr, first, last, -2, trlink);
		  trlink = ssize - 2;
		}
		if((a - first) <= (last - b)) {
		  if(1 < (a - first)) {
			STACK_PUSH5(ISAd, b, last, tr_ilg(last - b), trlink);
			last = a, limit = tr_ilg(a - first);
		  } else if(1 < (last - b)) {
			first = b, limit = tr_ilg(last - b);
		  } else {
			STACK_POP5(ISAd, first, last, limit, trlink);
		  }
		} else {
		  if(1 < (last - b)) {
			STACK_PUSH5(ISAd, first, a, tr_ilg(a - first), trlink);
			first = b, limit = tr_ilg(last - b);
		  } else if(1 < (a - first)) {
			last = a, limit = tr_ilg(a - first);
		  } else {
			STACK_POP5(ISAd, first, last, limit, trlink);
		  }
		}
	  } else if(limit == -2) {
		/* tandem repeat copy */
		a = stack[--ssize].b, b = stack[ssize].c;
		if(stack[ssize].d == 0) {
		  tr_copy(ISA, SA, first, a, b, last, ISAd - ISA);
		} else {
		  if(0 <= trlink) { stack[trlink].d = -1; }
		  tr_partialcopy(ISA, SA, first, a, b, last, ISAd - ISA);
		}
		STACK_POP5(ISAd, first, last, limit, trlink);
	  } else {
		/* sorted partition */
		if(0 <= *first) {
		  a = first;
		  do { ISA[*a] = a - SA; } while((++a < last) && (0 <= *a));
		  first = a;
		}
		if(first < last) {
		  a = first; do { *a = ~*a; } while(*++a < 0);
		  next = (ISA[*a] != ISAd[*a]) ? tr_ilg(a - first + 1) : -1;
		  if(++a < last) { for(b = first, v = a - SA - 1; b < a; ++b) { ISA[*b] = v; } }

		  /* push */
		  if(trbudget_check(budget, a - first)) {
			if((a - first) <= (last - a)) {
			  STACK_PUSH5(ISAd, a, last, -3, trlink);
			  ISAd += incr, last = a, limit = next;
			} else {
			  if(1 < (last - a)) {
				STACK_PUSH5(ISAd + incr, first, a, next, trlink);
				first = a, limit = -3;
			  } else {
				ISAd += incr, last = a, limit = next;
			  }
			}
		  } else {
			if(0 <= trlink) { stack[trlink].d = -1; }
			if(1 < (last - a)) {
			  first = a, limit = -3;
			} else {
			  STACK_POP5(ISAd, first, last, limit, trlink);
			}
		  }
		} else {
		  STACK_POP5(ISAd, first, last, limit, trlink);
		}
	  }
	  continue;
	}

	if((last - first) <= TR_INSERTIONSORT_THRESHOLD) {
	  tr_insertionsort(ISAd, first, last);
	  limit = -3;
	  continue;
	}

	if(limit-- == 0) {
	  tr_heapsort(ISAd, first, last - first);
	  for(a = last - 1; first < a; a = b) {
		for(x = ISAd[*a], b = a - 1; (first <= b) && (ISAd[*b] == x); --b) { *b = ~*b; }
	  }
	  limit = -3;
	  continue;
	}

	/* choose pivot */
	a = tr_pivot(ISAd, first, last);
	SWAP(*first, *a);
	v = ISAd[*first];

	/* partition */
	tr_partition(ISAd, first, first + 1, last, &a, &b, v);
	if((last - first) != (b - a)) {
	  next = (ISA[*a] != v) ? tr_ilg(b - a) : -1;

	  /* update ranks */
	  for(c = first, v = a - SA - 1; c < a; ++c) { ISA[*c] = v; }
	  if(b < last) { for(c = a, v = b - SA - 1; c < b; ++c) { ISA[*c] = v; } }

	  /* push */
	  if((1 < (b - a)) && (trbudget_check(budget, b - a))) {
		if((a - first) <= (last - b)) {
		  if((last - b) <= (b - a)) {
			if(1 < (a - first)) {
			  STACK_PUSH5(ISAd + incr, a, b, next, trlink);
			  STACK_PUSH5(ISAd, b, last, limit, trlink);
			  last = a;
			} else if(1 < (last - b)) {
			  STACK_PUSH5(ISAd + incr, a, b, next, trlink);
			  first = b;
			} else {
			  ISAd += incr, first = a, last = b, limit = next;
			}
		  } else if((a - first) <= (b - a)) {
			if(1 < (a - first)) {
			  STACK_PUSH5(ISAd, b, last, limit, trlink);
			  STACK_PUSH5(ISAd + incr, a, b, next, trlink);
			  last = a;
			} else {
			  STACK_PUSH5(ISAd, b, last, limit, trlink);
			  ISAd += incr, first = a, last = b, limit = next;
			}
		  } else {
			STACK_PUSH5(ISAd, b, last, limit, trlink);
			STACK_PUSH5(ISAd, first, a, limit, trlink);
			ISAd += incr, first = a, last = b, limit = next;
		  }
		} else {
		  if((a - first) <= (b - a)) {
			if(1 < (last - b)) {
			  STACK_PUSH5(ISAd + incr, a, b, next, trlink);
			  STACK_PUSH5(ISAd, first, a, limit, trlink);
			  first = b;
			} else if(1 < (a - first)) {
			  STACK_PUSH5(ISAd + incr, a, b, next, trlink);
			  last = a;
			} else {
			  ISAd += incr, first = a, last = b, limit = next;
			}
		  } else if((last - b) <= (b - a)) {
			if(1 < (last - b)) {
			  STACK_PUSH5(ISAd, first, a, limit, trlink);
			  STACK_PUSH5(ISAd + incr, a, b, next, trlink);
			  first = b;
			} else {
			  STACK_PUSH5(ISAd, first, a, limit, trlink);
			  ISAd += incr, first = a, last = b, limit = next;
			}
		  } else {
			STACK_PUSH5(ISAd, first, a, limit, trlink);
			STACK_PUSH5(ISAd, b, last, limit, trlink);
			ISAd += incr, first = a, last = b, limit = next;
		  }
		}
	  } else {
		if((1 < (b - a)) && (0 <= trlink)) { stack[trlink].d = -1; }
		if((a - first) <= (last - b)) {
		  if(1 < (a - first)) {
			STACK_PUSH5(ISAd, b, last, limit, trlink);
			last = a;
		  } else if(1 < (last - b)) {
			first = b;
		  } else {
			STACK_POP5(ISAd, first, last, limit, trlink);
		  }
		} else {
		  if(1 < (last - b)) {
			STACK_PUSH5(ISAd, first, a, limit, trlink);
			first = b;
		  } else if(1 < (a - first)) {
			last = a;
		  } else {
			STACK_POP5(ISAd, first, last, limit, trlink);
		  }
		}
	  }
	} else {
	  if(trbudget_check(budget, last - first)) {
		limit = tr_ilg(last - first), ISAd += incr;
	  } else {
		if(0 <= trlink) { stack[trlink].d = -1; }
		STACK_POP5(ISAd, first, last, limit, trlink);
	  }
	}
  }
#undef STACK_SIZE
}

/*---------------------------------------------------------------------------*/

/*- Function -*/

/* Tandem repeat sort */
void
trsort(saidx_t *ISA, saidx_t *SA, saidx_t n, saidx_t depth) {
  saidx_t *ISAd;
  saidx_t *first, *last;
  trbudget_t budget;
  saidx_t t, skip, unsorted;

  trbudget_init(&budget, tr_ilg(n) * 2 / 3, n);
/*  trbudget_init(&budget, tr_ilg(n) * 3 / 4, n); */
  for(ISAd = ISA + depth; -n < *SA; ISAd += ISAd - ISA) {
	first = SA;
	skip = 0;
	unsorted = 0;
	do {
	  if((t = *first) < 0) { first -= t; skip += t; }
	  else {
		if(skip != 0) { *(first + skip) = skip; skip = 0; }
		last = SA + ISA[t] + 1;
		if(1 < (last - first)) {
		  budget.count = 0;
		  tr_introsort(ISA, ISAd, SA, first, last, &budget);
		  if(budget.count != 0) { unsorted += budget.count; }
		  else { skip = first - last; }
		} else if((last - first) == 1) {
		  skip = -1;
		}
		first = last;
	  }
	} while(first < (SA + n));
	if(skip != 0) { *(first + skip) = skip; }
	if(unsorted == 0) { break; }
  }
}

/*** End of inlined file: trsort.c ***/



/*** Start of inlined file: utils.c ***/
//#include "divsufsort_private.h"

/*- Private Function -*/

/* Binary search for inverse bwt. */
static
saidx_t
binarysearch_lower(const saidx_t *A, saidx_t size, saidx_t value) {
  saidx_t half, i;
  for(i = 0, half = size >> 1;
	  0 < size;
	  size = half, half >>= 1) {
	if(A[i + half] < value) {
	  i += half + 1;
	  half -= (size & 1) ^ 1;
	}
  }
  return i;
}

/*- Functions -*/

/* Burrows-Wheeler transform. */
saint_t
bw_transform(const sauchar_t *T, sauchar_t *U, saidx_t *SA,
			 saidx_t n, saidx_t *idx) {
  saidx_t *A, i, j, p, t;
  saint_t c;

  /* Check arguments. */
  if((T == NULL) || (U == NULL) || (n < 0) || (idx == NULL)) { return -1; }
  if(n <= 1) {
	if(n == 1) { U[0] = T[0]; }
	*idx = n;
	return 0;
  }

  if((A = SA) == NULL) {
	i = divbwt(T, U, NULL, n);
	if(0 <= i) { *idx = i; i = 0; }
	return (saint_t)i;
  }

  /* BW transform. */
  if(T == U) {
	t = n;
	for(i = 0, j = 0; i < n; ++i) {
	  p = t - 1;
	  t = A[i];
	  if(0 <= p) {
		c = T[j];
		U[j] = (j <= p) ? T[p] : (sauchar_t)A[p];
		A[j] = c;
		j++;
	  } else {
		*idx = i;
	  }
	}
	p = t - 1;
	if(0 <= p) {
	  c = T[j];
	  U[j] = (j <= p) ? T[p] : (sauchar_t)A[p];
	  A[j] = c;
	} else {
	  *idx = i;
	}
  } else {
	U[0] = T[n - 1];
	for(i = 0; A[i] != 0; ++i) { U[i + 1] = T[A[i] - 1]; }
	*idx = i + 1;
	for(++i; i < n; ++i) { U[i] = T[A[i] - 1]; }
  }

  if(SA == NULL) {
	/* Deallocate memory. */
	free(A);
  }

  return 0;
}

/* Inverse Burrows-Wheeler transform. */
saint_t
inverse_bw_transform(const sauchar_t *T, sauchar_t *U, saidx_t *A,
					 saidx_t n, saidx_t idx) {
  saidx_t C[ALPHABET_SIZE];
  sauchar_t D[ALPHABET_SIZE];
  saidx_t *B;
  saidx_t i, p;
  saint_t c, d;

  /* Check arguments. */
  if((T == NULL) || (U == NULL) || (n < 0) || (idx < 0) ||
	 (n < idx) || ((0 < n) && (idx == 0))) {
	return -1;
  }
  if(n <= 1) { return 0; }

  if((B = A) == NULL) {
	/* Allocate n*sizeof(saidx_t) bytes of memory. */
	if((B = (saidx_t *)malloc((size_t)n * sizeof(saidx_t))) == NULL) { return -2; }
  }

  /* Inverse BW transform. */
  for(c = 0; c < ALPHABET_SIZE; ++c) { C[c] = 0; }
  for(i = 0; i < n; ++i) { ++C[T[i]]; }
  for(c = 0, d = 0, i = 0; c < ALPHABET_SIZE; ++c) {
	p = C[c];
	if(0 < p) {
	  C[c] = i;
	  D[d++] = (sauchar_t)c;
	  i += p;
	}
  }
  for(i = 0; i < idx; ++i) { B[C[T[i]]++] = i; }
  for( ; i < n; ++i)       { B[C[T[i]]++] = i + 1; }
  for(c = 0; c < d; ++c) { C[c] = C[D[c]]; }
  for(i = 0, p = idx; i < n; ++i) {
	U[i] = D[binarysearch_lower(C, d, p)];
	p = B[p - 1];
  }

  if(A == NULL) {
	/* Deallocate memory. */
	free(B);
  }

  return 0;
}

/* Checks the suffix array SA of the string T. */
saint_t
sufcheck(const sauchar_t *T, const saidx_t *SA,
		 saidx_t n, saint_t verbose) {
  saidx_t C[ALPHABET_SIZE];
  saidx_t i, p, q, t;
  saint_t c;

  if(verbose) { fprintf(stderr, "sufcheck: "); }

  /* Check arguments. */
  if((T == NULL) || (SA == NULL) || (n < 0)) {
	if(verbose) { fprintf(stderr, "Invalid arguments.\n"); }
	return -1;
  }
  if(n == 0) {
	if(verbose) { fprintf(stderr, "Done.\n"); }
	return 0;
  }

  /* check range: [0..n-1] */
  for(i = 0; i < n; ++i) {
	if((SA[i] < 0) || (n <= SA[i])) {
	  if(verbose) {
		fprintf(stderr, "Out of the range [0,%" PRIdSAIDX_T "].\n"
						"  SA[%" PRIdSAIDX_T "]=%" PRIdSAIDX_T "\n",
						n - 1, i, SA[i]);
	  }
	  return -2;
	}
  }

  /* check first characters. */
  for(i = 1; i < n; ++i) {
	if(T[SA[i - 1]] > T[SA[i]]) {
	  if(verbose) {
		fprintf(stderr, "Suffixes in wrong order.\n"
						"  T[SA[%" PRIdSAIDX_T "]=%" PRIdSAIDX_T "]=%d"
						" > T[SA[%" PRIdSAIDX_T "]=%" PRIdSAIDX_T "]=%d\n",
						i - 1, SA[i - 1], T[SA[i - 1]], i, SA[i], T[SA[i]]);
	  }
	  return -3;
	}
  }

  /* check suffixes. */
  for(i = 0; i < ALPHABET_SIZE; ++i) { C[i] = 0; }
  for(i = 0; i < n; ++i) { ++C[T[i]]; }
  for(i = 0, p = 0; i < ALPHABET_SIZE; ++i) {
	t = C[i];
	C[i] = p;
	p += t;
  }

  q = C[T[n - 1]];
  C[T[n - 1]] += 1;
  for(i = 0; i < n; ++i) {
	p = SA[i];
	if(0 < p) {
	  c = T[--p];
	  t = C[c];
	} else {
	  c = T[p = n - 1];
	  t = q;
	}
	if((t < 0) || (p != SA[t])) {
	  if(verbose) {
		fprintf(stderr, "Suffix in wrong position.\n"
						"  SA[%" PRIdSAIDX_T "]=%" PRIdSAIDX_T " or\n"
						"  SA[%" PRIdSAIDX_T "]=%" PRIdSAIDX_T "\n",
						t, (0 <= t) ? SA[t] : -1, i, SA[i]);
	  }
	  return -4;
	}
	if(t != q) {
	  ++C[c];
	  if((n <= C[c]) || (T[SA[C[c]]] != c)) { C[c] = -1; }
	}
  }

  if(1 <= verbose) { fprintf(stderr, "Done.\n"); }
  return 0;
}

static
int
_compare(const sauchar_t *T, saidx_t Tsize,
		 const sauchar_t *P, saidx_t Psize,
		 saidx_t suf, saidx_t *match) {
  saidx_t i, j;
  saint_t r;
  for(i = suf + *match, j = *match, r = 0;
	  (i < Tsize) && (j < Psize) && ((r = T[i] - P[j]) == 0); ++i, ++j) { }
  *match = j;
  return (r == 0) ? -(j != Psize) : r;
}

/* Search for the pattern P in the string T. */
saidx_t
sa_search(const sauchar_t *T, saidx_t Tsize,
		  const sauchar_t *P, saidx_t Psize,
		  const saidx_t *SA, saidx_t SAsize,
		  saidx_t *idx) {
  saidx_t size, lsize, rsize, half;
  saidx_t match, lmatch, rmatch;
  saidx_t llmatch, lrmatch, rlmatch, rrmatch;
  saidx_t i, j, k;
  saint_t r;

  if(idx != NULL) { *idx = -1; }
  if((T == NULL) || (P == NULL) || (SA == NULL) ||
	 (Tsize < 0) || (Psize < 0) || (SAsize < 0)) { return -1; }
  if((Tsize == 0) || (SAsize == 0)) { return 0; }
  if(Psize == 0) { if(idx != NULL) { *idx = 0; } return SAsize; }

  for(i = j = k = 0, lmatch = rmatch = 0, size = SAsize, half = size >> 1;
	  0 < size;
	  size = half, half >>= 1) {
	match = MIN(lmatch, rmatch);
	r = _compare(T, Tsize, P, Psize, SA[i + half], &match);
	if(r < 0) {
	  i += half + 1;
	  half -= (size & 1) ^ 1;
	  lmatch = match;
	} else if(r > 0) {
	  rmatch = match;
	} else {
	  lsize = half, j = i, rsize = size - half - 1, k = i + half + 1;

	  /* left part */
	  for(llmatch = lmatch, lrmatch = match, half = lsize >> 1;
		  0 < lsize;
		  lsize = half, half >>= 1) {
		lmatch = MIN(llmatch, lrmatch);
		r = _compare(T, Tsize, P, Psize, SA[j + half], &lmatch);
		if(r < 0) {
		  j += half + 1;
		  half -= (lsize & 1) ^ 1;
		  llmatch = lmatch;
		} else {
		  lrmatch = lmatch;
		}
	  }

	  /* right part */
	  for(rlmatch = match, rrmatch = rmatch, half = rsize >> 1;
		  0 < rsize;
		  rsize = half, half >>= 1) {
		rmatch = MIN(rlmatch, rrmatch);
		r = _compare(T, Tsize, P, Psize, SA[k + half], &rmatch);
		if(r <= 0) {
		  k += half + 1;
		  half -= (rsize & 1) ^ 1;
		  rlmatch = rmatch;
		} else {
		  rrmatch = rmatch;
		}
	  }

	  break;
	}
  }

  if(idx != NULL) { *idx = (0 < (k - j)) ? j : i; }
  return k - j;
}

/* Search for the character c in the string T. */
saidx_t
sa_simplesearch(const sauchar_t *T, saidx_t Tsize,
				const saidx_t *SA, saidx_t SAsize,
				saint_t c, saidx_t *idx) {
  saidx_t size, lsize, rsize, half;
  saidx_t i, j, k, p;
  saint_t r;

  if(idx != NULL) { *idx = -1; }
  if((T == NULL) || (SA == NULL) || (Tsize < 0) || (SAsize < 0)) { return -1; }
  if((Tsize == 0) || (SAsize == 0)) { return 0; }

  for(i = j = k = 0, size = SAsize, half = size >> 1;
	  0 < size;
	  size = half, half >>= 1) {
	p = SA[i + half];
	r = (p < Tsize) ? T[p] - c : -1;
	if(r < 0) {
	  i += half + 1;
	  half -= (size & 1) ^ 1;
	} else if(r == 0) {
	  lsize = half, j = i, rsize = size - half - 1, k = i + half + 1;

	  /* left part */
	  for(half = lsize >> 1;
		  0 < lsize;
		  lsize = half, half >>= 1) {
		p = SA[j + half];
		r = (p < Tsize) ? T[p] - c : -1;
		if(r < 0) {
		  j += half + 1;
		  half -= (lsize & 1) ^ 1;
		}
	  }

	  /* right part */
	  for(half = rsize >> 1;
		  0 < rsize;
		  rsize = half, half >>= 1) {
		p = SA[k + half];
		r = (p < Tsize) ? T[p] - c : -1;
		if(r <= 0) {
		  k += half + 1;
		  half -= (rsize & 1) ^ 1;
		}
	  }

	  break;
	}
  }

  if(idx != NULL) { *idx = (0 < (k - j)) ? j : i; }
  return k - j;
}

/*** End of inlined file: utils.c ***/

/*** End of inlined file: mydivsufsort2.c ***/
