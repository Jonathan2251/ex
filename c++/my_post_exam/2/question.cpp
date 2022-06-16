/*
(a). Reading an article from input file, in.txt, and adjust it to 60 charactors each line with insert blank between words.
Remember do not truncate words. Both "summer," and "days." are not truncatable.

For example:

input:
"The town revolved around the river. In \
summer, when the blazing sun beat down, it dozed \
under the weight of sultry days. On Main Street a \
sow and her litter of pigs might root along the wooden \
sidwal, sharing the deeply rutted roadway with \
foraging hens and a hound languidly cratching his \
fleas.";

output:
> input width : 60
123456789012345678901234567890123456789012345678901234567890
The  town  revolved  around  the  river. In summer, when the
blazing  sun  beat down, it dozed under the weight of sultry
days. On Main Street a sow and her litter of pigs might root
along  the  wooden sidwal, sharing the deeply rutted roadway
with  foraging  hens  and  a  hound  languidly cratching his
fleas. 

(b). 60 charactors each line at maximum on 6 lines and the charactors in each line is as close as possible.

input:
Same as (a).

output:
123456789012345678901234567890123456789012345678901234567890
The   town  revolved  around  the  river.  In  summer,  when
the   blazing   sun   beat   down,   it   dozed   under  the
weight  of  sultry  days.  On  Main  Street  a  sow  and her
litter   of   pigs  might  root  along  the  wooden  sidwal,
sharing    the   deeply   rutted   roadway   with   foraging
hens   and   a   hound   languidly   cratching   his  fleas.
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std ;

char inStr[] = 
"The town revolved around the river. In \
summer, when the blazing sun beat down, it dozed \
under the weight of sultry days. On Main Street a \
sow and her litter of pigs might root along the wooden \
sidwal, sharing the deeply rutted roadway with \
foraging hens and a hound languidly cratching his \
fleas.";

int main() {
  printf("%s\n", inStr);
}
