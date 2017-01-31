#include <iostream>
#include <vector>
using namespace std;

class FunctionalReactiveNode {
public:
	int value;
	vector<FunctionalReactiveNode*> subscribers;

	FunctionalReactiveNode (int v, vector<FunctionalReactiveNode*> s){
		value = v;
		subscribers = s;
	}

	void addSubscriber(FunctionalReactiveNode* sub){
		vector<FunctionalReactiveNode*> s = subscribers;
		s.push_back(sub);

		//replace Object with a new Object
		*this = FunctionalReactiveNode(value, s);
	}

	void setValue(int newValue){
		//notify all subscribers
		for(FunctionalReactiveNode* node: subscribers){
			node->setValue(node->value + newValue - value);
		}

		//replace Object with a new Object
		*this = FunctionalReactiveNode(newValue, subscribers);
	}

	static FunctionalReactiveNode* addition(FunctionalReactiveNode &a, FunctionalReactiveNode &b){
		FunctionalReactiveNode* res = new FunctionalReactiveNode(a.value + b.value, vector<FunctionalReactiveNode*>());
		a.addSubscriber(res);
		b.addSubscriber(res);

		return res;
	}
};

int main(){

	FunctionalReactiveNode *a = new FunctionalReactiveNode(5, vector<FunctionalReactiveNode*>());
	FunctionalReactiveNode *b = new FunctionalReactiveNode(5, vector<FunctionalReactiveNode*>());
	FunctionalReactiveNode *c = FunctionalReactiveNode::addition(*a, *b);
	FunctionalReactiveNode *d = FunctionalReactiveNode::addition(*c, *b);

	cout << "c: " << c->value << endl; // c: 10
	cout << "d: " << d->value << endl; // d: 15

	a->setValue(10);
	cout << "c: " << c->value << endl; // c: 15
	cout << "d: " << d->value << endl; // d: 20

	b->setValue(1);
	cout << "c: " << c->value << endl; // c: 11
	cout << "d: " << d->value << endl; // d: 12

	return 0;
}

