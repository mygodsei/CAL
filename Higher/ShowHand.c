#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef enum esuit {
  SPADES, 
  HEARTS, 
  DIAMONDS, 
  CLUBS
} Suit;

typedef enum eface {
  ACE,
  DEUCE,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  TEN,
  JACK,
  QUEEN,
  KING
} Face;
typedef struct Card {
  Suit suit;
  Face face;
}Card;
typedef char Str[50];
typedef Card Hand[5];
int OrderSuit(Suit suit);
int OrderFace(Face face);
bool Same(Face face1 , Face face2);
void PrintCard(Card card);
bool InputHand(Hand hand);
void PrintHand(Hand hand);
bool BiggerThan(Card card1, Card card2);
Card FindLargest(Hand hand);
bool IsFlush(Hand hand);
bool IsStraight(Hand hand);
bool IsStraightFlush(Hand hand);
bool IsFourOfAKind(Hand hand);
bool HasThreeOfAKind(Hand hand);
bool IsTwoPairs(Hand hand);
bool HasOnePair(Hand hand);
bool IsFullHouse(Hand hand);
bool IsZilch(Hand hand);
bool CompareTwoPair(Hand hand1 , Hand hand2);
int Set(Hand hand);
int PrintSet(Hand hand, int set, int num);
void Play(Hand hand1, Hand hand2);
int main() {
  Hand firsthand, secondhand;
  int i;
  const char* input_error[2] = {"Input Error in first hand of cards!\n",
                                "Input Error in second hand of cards!\n"};
  if (InputHand(firsthand) == false) {
    i = 0;
    printf("%s", input_error[i]);
    return 0;
  } 
  if (InputHand(secondhand) == false) {
    i = 1;
    printf("%s", input_error[i]);
    return 0;
  }
  
  Play(firsthand, secondhand);
  return 0;
}
int OrderSuit(Suit suit) {
  switch (suit) {
    case SPADES: return 4;
    case HEARTS: return 3;
    case CLUBS: return 2;
    case DIAMONDS: return 1;
  }
}
int OrderFace(Face face) {
  switch (face) {
    case ACE: return 13;
    case KING: return 12;
    case QUEEN: return 11;
    case JACK: return 10;
    case TEN: return 9;
    case NINE: return 8;
    case EIGHT: return 7;
    case SEVEN: return 6;
    case SIX: return 5;
    case FIVE: return 4;
    case FOUR: return 3;
    case THREE: return 2;
    case DEUCE: return 1;
  }
}
bool Same(Face face1 , Face face2) {
  if (face1 == face2) return true;
  else return false;
}
void PrintCard(Card card) {
  const char* face_names[13] = {
  "Ace of ", "Deuce of ", "Three of ", "Four of ", "Five of ",
  "Six of ", "Seven of ", "Eight of ", "Nine of ", "Ten of ",
  "Jack of ", "Queen of ", "King of "};
  const char* suit_names[4] = {"Spades", "Hearts", "Diamonds", "Clubs"};
  switch (card.face) {
    case ACE: printf("%s", face_names[0]); break;
    case DEUCE: printf("%s", face_names[1]); break;
    case THREE: printf("%s", face_names[2]); break;
    case FOUR: printf("%s", face_names[3]); break;
    case FIVE: printf("%s", face_names[4]); break;
    case SIX: printf("%s", face_names[5]); break;
    case SEVEN: printf("%s", face_names[6]); break;
    case EIGHT: printf("%s", face_names[7]); break;
    case NINE: printf("%s", face_names[8]); break;
    case TEN: printf("%s", face_names[9]); break;
    case JACK: printf("%s", face_names[10]); break;
    case QUEEN: printf("%s", face_names[11]); break;
    case KING: printf("%s", face_names[12]); break;
  }
  switch (card.suit) {
    case SPADES: printf("%s", suit_names[0]); break;
    case HEARTS: printf("%s", suit_names[1]); break;
    case DIAMONDS: printf("%s", suit_names[2]); break;
    case CLUBS: printf("%s", suit_names[3]); break;
  }
}

bool InputHand(Hand hand) {
  int c = 0;
  char in1[100] , in2[100];
  while (1) {
    scanf(" %s", in1);
    if (strcmp(in1 , "H") == 0) hand[c].suit = HEARTS;
    else if (strcmp(in1 , "S") == 0) hand[c].suit = SPADES;
    else if (strcmp(in1 , "C") == 0) hand[c].suit = CLUBS;
    else if (strcmp(in1 , "D") == 0) hand[c].suit = DIAMONDS;
    else if (strcmp(in1 , "-1") == 0) break;
    else return false;
    scanf(" %s" , in2);
    if (strcmp(in2 , "A") == 0) hand[c].face = ACE;
    else if (strcmp(in2 , "2") == 0) hand[c].face = DEUCE;
    else if (strcmp(in2 , "3") == 0) hand[c].face = THREE;
    else if (strcmp(in2 , "4") == 0) hand[c].face = FOUR;
    else if (strcmp(in2 , "5") == 0) hand[c].face = FIVE;
    else if (strcmp(in2 , "6") == 0) hand[c].face = SIX;
    else if (strcmp(in2 , "7") == 0) hand[c].face = SEVEN;
    else if (strcmp(in2 , "8") == 0) hand[c].face = EIGHT;
    else if (strcmp(in2 , "9") == 0) hand[c].face = NINE;
    else if (strcmp(in2 , "10") == 0) hand[c].face = TEN;
    else if (strcmp(in2 , "J") == 0) hand[c].face = JACK;
    else if (strcmp(in2 , "Q") == 0) hand[c].face = QUEEN;
    else if (strcmp(in2 , "K") == 0) hand[c].face = KING;
    else return false;
    c++;
  }
  if (c != 5) {
    return false;
  }
  return true;
}
void PrintHand(Hand hand) {
  const char* face_names[13] = {
  "Ace of ", "Deuce of ", "Three of ", "Four of ", "Five of ",
  "Six of ", "Seven of ", "Eight of ", "Nine of ", "Ten of ",
  "Jack of ", "Queen of ", "King of "};
  const char* suit_names[4] = {"Spades", "Hearts", "Diamonds", "Clubs"};
  for (int i = 0; i < 5; i++) {
    if (hand[i].face == ACE) printf("%s", face_names[0]);
    else if (hand[i].face == DEUCE) printf("%s", face_names[1]);
    else if (hand[i].face == THREE) printf("%s", face_names[2]);
    else if (hand[i].face == FOUR) printf("%s", face_names[3]);
    else if (hand[i].face == FIVE) printf("%s", face_names[4]);
    else if (hand[i].face == SIX) printf("%s", face_names[5]);
    else if (hand[i].face == SEVEN) printf("%s", face_names[6]);
    else if (hand[i].face == EIGHT) printf("%s", face_names[7]);
    else if (hand[i].face == NINE) printf("%s", face_names[8]);
    else if (hand[i].face == TEN) printf("%s", face_names[9]);
    else if (hand[i].face == JACK) printf("%s", face_names[10]);
    else if (hand[i].face == QUEEN) printf("%s", face_names[11]);
    else if (hand[i].face == KING) printf("%s", face_names[12]);

    if (hand[i].suit == SPADES) printf("%s\n", suit_names[0]);
    else if (hand[i].suit == HEARTS) printf("%s\n", suit_names[1]);
    else if (hand[i].suit == DIAMONDS) printf("%s\n", suit_names[2]);
    else if (hand[i].suit == CLUBS) printf("%s\n", suit_names[3]);
  }
}
bool BiggerThan(Card card1, Card card2) {
  int  c1 , c2;
  c1 = OrderFace(card1.face);
  c2 = OrderFace(card2.face);
  if (c2 > c1) return false;
  else if (c1 > c2) return true;
  else if (c1 == c2) {
    c1 = OrderSuit(card1.suit);
    c2 = OrderSuit(card2.suit);
    if (c2 > c1) return false;
    else if (c1 > c2) return true;
  } 
  return true;
}
Card FindLargest(Hand hand) {
  bool test = false , t = false;
  int num = 0 , h;
  for (int i = 0; i < 5; i++) {
    h = OrderFace(hand[i].face);
    if (h == 13 || h == 1 || h == 2 || h== 3 || h== 4) t = true;
    else {
      t = false;
      break;
    }
  }
  if (t) {
    for (int i = 0; i < 5; i++) {
      if (OrderFace(hand[i].face) == 4) return hand[i];
    }
  }
  for (int i = 0; i < 5; i++) {
    test = BiggerThan(hand[i] , hand[num]);
    if (test) num = i;
  }
  return hand[num];
}
bool IsFlush(Hand hand) {
  int s;
  Card temp;
  s = OrderSuit(hand[0].suit);
  for (int i = 0; i < 5; i++) {
    int t = OrderSuit(hand[i].suit);
    if (t != s) return false;
  }
  temp = FindLargest(hand);
  for (int i = 0; i < 5; i++) {
    if (hand[i].face == temp.face) {
      temp = hand[i];
      hand[i] = hand[0];
      hand[0] = temp;
    }
  }
  return true; 
}
bool IsStraight(Hand hand) {
  int h;
  bool j = false;
  for (int i = 0; i < 5; i++) {
    h = OrderFace(hand[i].face);
    if (h == 13 || h == 1 || h == 2 || h== 3 || h== 4) j = true;
    else {
      j = false;
      break;
    }
  }
  if (j) {
    for (int i = 0; i < 5; i++) {
      if (OrderFace(hand[i].face) == 4) {
        Card temp = hand[i];
        hand[i] = hand[0];
        hand[0] = temp;
        return true;
      }
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = i + 1; j < 5; j++) {
      if (OrderFace(hand[i].face) > OrderFace(hand[j].face)) {
        Card temp = hand[i];
        hand[i] = hand[j];
        hand[j] = temp;
      }
    }
  }
  bool s = true;
  for (int i = 0; i < 4; i++) {
    if (OrderFace(hand[i].face) + 1 != OrderFace(hand[i + 1].face)) {
      s = false;
      break;
    }
  }
  if (s) {
    Card largest = FindLargest(hand);
    for (int i = 0; i < 5; i++) {
      if (hand[i].face == largest.face) {
        Card temp = hand[i];
        hand[i] = hand[0];
        hand[0] = temp;
        break;
      }
    }
    return true;
  } else {
    return false;
  }
}
bool IsStraightFlush(Hand hand) {
  bool isf;
  isf = IsFlush(hand);
  if (isf) {
    bool iss;
    iss = IsStraight(hand);
    if (iss) return true;
    else return false;
   
  } else {
    return false;
  }

}
bool IsFourOfAKind(Hand hand) {
  Card largest; 
  int s = 0;  
  Card test = hand[0];
  for (int i = 0; i < 5; i++) {
    int b = 0;
    for (int j = 0; j < 5; j++) {
      if (Same(hand[i].face , hand[j].face)) {
        b++;
      }
    } 
    if (b == 4) {
      s = b;
      test.face = hand[i].face;
      break;
    }
  }
  if (s != 4) return false;
  Card bigsuit;
  Card bigcard;
  int g = -1;
  bigsuit = hand[0]; 
  for (int i = 0; i < 5; i++) {
    if (hand[i].face == test.face) {
      if (g == -1 || BiggerThan(hand[i], bigsuit)) {
        bigsuit = hand[i]; 
        g = i;             
      }
    }
  }
  if (g != -1) {
    Card temp = hand[g];
    hand[g] = hand[0];
    hand[0] = temp;
  }

  return true;
}
bool HasThreeOfAKind(Hand hand) {  
  Card largest; 
  int s = 0;  
  Card test = hand[0] , test2;
  for (int i = 0; i < 5; i++) {
    int b = 0;
    for (int j = 0; j < 5; j++) {
      if (Same(hand[i].face , hand[j].face)) {
        b++;
      }
    } 
    if (b == 3) {
      s = b;
      test.face = hand[i].face;
    } else if (b == 2) {
      return false; 
    }
  }
  if (s != 3) return false;
  Card bigsuit;
  Card bigcard;
  int g = -1;
  bigsuit = hand[0]; 
  for (int i = 0; i < 5; i++) {
    if (hand[i].face == test.face) {
      if (g == -1 || BiggerThan(hand[i], bigsuit)) {
        bigsuit = hand[i]; 
        g = i;             
      }
    }
  }
  if (g != -1) {
    Card temp = hand[g];
    hand[g] = hand[0];
    hand[0] = temp;
  }
  return true;
}
bool IsTwoPairs(Hand hand) {
  Card largest; 
  int s = 0 , t = 0;  
  Card test1 , test2 = hand[0];
  test1.suit = -1;
  test2.face = -1;
  for (int i = 0; i < 5; i++) {
    int b = 0;
    for (int j = 0; j < 5; j++) {
      if (Same(hand[i].face , hand[j].face) && hand[i].face != test1.face) {
        b++;
      }
    } 
    if (b == 2 && t == 0) {
      test1.face = hand[i].face;
      t++;
    } else if (b == 2 && t == 1) {
      test2.face = hand[i].face;
      t++;
      break;
    }
  }
  if (t != 2) return false;
  Card bigsuit;
  Card bigcard;
  int g = -1;
  int h = -1;
  bigsuit = hand[0]; 
  for (int i = 0; i < 5; i++) {
    if (hand[i].face == test1.face) {
      if (g == -1 || BiggerThan(hand[i], bigsuit)) {
        bigsuit = hand[i]; 
        g = i;             
      }
    } else if (hand[i].face == test2.face) {
      if (h == -1 || BiggerThan(hand[i], bigsuit)) {
        bigsuit = hand[i]; 
        h = i;             
      }
    }
  }
  Card temp1 , temp2;
  if (test2.face > test1.face) {
    temp1 = hand[g];
    temp2 = hand[h];
    hand[g] = hand[0];
    hand[h] = hand[1];
    hand[0] = temp2;
    hand[1] = temp1;
  } else if (test2.face < test1.face) { 
    temp1 = hand[g];
    temp2 = hand[h];
    hand[0] = temp1;    
    hand[1] = temp2;
  } 
  return true;
}
bool HasOnePair(Hand hand) {
  Card largest; 
  int s = 0 , t = 0;  
  Card test = hand[0];
  for (int i = 0; i < 5; i++) {
    int b = 0;
    for (int j = 0; j < 5; j++) {
      if (Same(hand[i].face , hand[j].face)) {
        b++;
      }
    } 
    if (b == 2) {
      t++;
      s = b;
      test.face = hand[i].face;
    }
  }
  if (s != 2) return false;
  Card bigsuit;
  Card bigcard;
  int g = -1;
  bigsuit = hand[0]; 
  for (int i = 0; i < 5; i++) {
    if (hand[i].face == test.face) {
      if (g == -1 || BiggerThan(hand[i], bigsuit)) {
        bigsuit = hand[i]; 
        g = i;             
      }
    }
  }

  if (g != -1) {
    Card temp = hand[g];
    hand[g] = hand[0];
    hand[0] = temp;
  }

  return true;
}
bool IsFullHouse(Hand hand) {
  Card largest; 
  int s = 0 , t1 = 0 , t2 = 0;  
  Card test1 , test2;
  test2.face = -1;
  test1.face = -1;
  for (int i = 0; i < 5; i++) {
    int b = 0;
    for (int j = 0; j < 5; j++) {
      if (Same(hand[i].face , hand[j].face)) {
        if (hand[i].face != test2.face && hand[i].face != test1.face) b++;
      }
    } 
    if (b == 3) {
      test1.face = hand[i].face;
      t1++;
    } else if (b == 2) {
      test2.face = hand[i].face;
      t2++;
    }
  }
  if (t1 != 1) return false;
  if (t2 != 1) return false;
  Card bigsuit;
  Card bigcard;
  int g = -1;
  int h = -1;
  bigsuit.suit = -1;
  bigsuit.face = -1;
  for (int i = 0; i < 5; i++) {
    if (hand[i].face == test1.face) {
      if (g == -1 || BiggerThan(hand[i], bigsuit)) {
        bigsuit = hand[i]; 
        g = i;             
      }
    }
  }
  if (g != -1) {
    Card temp = hand[g];
    hand[g] = hand[0];
    hand[0] = temp;
  }
  return true;
}
bool IsZilch(Hand hand) {
  int t;
  for (int i = 0; i < 5; i++) {
    for (int j = i+1; j < 5; j++) {
      if (hand[i].face == hand[j].face) return false;
    }
  }
  Card big = FindLargest(hand);
  for (int i = 0; i < 5; i++) {
    int t = i;
    for (int j = i+1; j < 5; j++) {
      if (BiggerThan(hand[j] , hand[t])) {
        t = j;
      }
    }
    Card temp = hand[i];
    hand[i] = hand[t];
    hand[t] = temp;
  }
  for (int i = 0; i < 5; i++) {
    if (hand[i].face == big.face && hand[i].suit == big.suit) {
      t = i;
    }
  }
  Card temp = hand[t];
  hand[t] = hand[0];
  hand[0] = temp;
  return true;
}
bool CompareTwoPair(Hand hand1 , Hand hand2) {
  if (Same(hand1[0].face , hand2[0].face)) {
    if (Same(hand1[1].face , hand2[1].face)) {
      if (BiggerThan(hand1[0] , hand2[0])) return true;
      else return false;
    }
  } else {
    if (BiggerThan(hand1[0] , hand2[0])) return true;
    else return false;
  }
}
int Set(Hand hand) {
  int t = 0;
  if (IsStraightFlush(hand)) t = 9;
  else if (IsFourOfAKind(hand)) t = 8;
  else if (IsFullHouse(hand)) t = 7;
  else if (IsFlush(hand)) t = 6;
  else if (IsStraight(hand)) t = 5;
  else if (HasThreeOfAKind(hand)) t = 4;
  else if (IsTwoPairs(hand)) t = 3;
  else if (HasOnePair(hand)) t = 2;
  else if (IsZilch(hand)) t = 1;
  return t;
}
int PrintSet(Hand hand, int set, int num) {
  if (set != 3) {
    if (num == 1) {
      if (set == 9) printf("Straight flush");
      else if (set == 8) printf("Four of a kind");
      else if (set == 7) printf("Full house");
      else if (set == 6) printf("Flush");
      else if (set == 5) printf("Straight");
      else if (set == 4) printf("Three of a kind");
      else if (set == 2) printf("One pair");
      else if (set == 1) printf("Zilch");
    } else {
      if (set == 9) printf("straight flush");
      else if (set == 8) printf("four of a kind");
      else if (set == 7) printf("full house");
      else if (set == 6) printf("flush");
      else if (set == 5) printf("straight");
      else if (set == 4) printf("three of a kind");
      else if (set == 2) printf("one pair");
      else if (set == 1) printf("zilch");
    }
    printf(" (");
    PrintCard(hand[0]);
    printf(")");
  } else if (set == 3) {
    if (num == 1) {
      printf("Two pairs (");
    } else {
      printf("two pairs (");
    }
    PrintCard(hand[0]);
    printf(" and ");
    PrintCard(hand[1]);
    printf(")");
  }
}
void Play(Hand hand1, Hand hand2) {
  int card = 1;
  int first = Set(hand1);
  int second = Set(hand2);
  if (first > second) {
    PrintSet(hand1, first, card);
    printf(" wins over ");
    PrintSet(hand2, second, card + 1);
  } else if (first < second) {
    PrintSet(hand1, first, card);
    printf(" loses to ");
    PrintSet(hand2, second, card + 1);
  } else {
    if (CompareTwoPair(hand1, hand2)) {
      PrintSet(hand1, first, card);
      printf(" wins over ");
      PrintSet(hand2, second, card + 1);
    } else {
      PrintSet(hand1, first, card);
      printf(" loses to ");
      PrintSet(hand2, second, card + 1);
    }
  }
  printf(".");
}