class Rational {
public:
    Rational() {
        num = 0;
        den = 1;
    }

    Rational(int numerator, int denominator) {
        if (denominator < 0) {
            if (numerator < 0) {
                denominator = abs(denominator);
                numerator = abs(numerator);
            } else {
                denominator = abs(denominator);
                numerator = numerator - 2 * numerator;
            }
        }
        if (numerator == 0) {
            denominator = 1;
        }

        int nod = Nod(abs(numerator), abs(denominator));
        num = numerator / nod;
        den = denominator / nod;

    }

    int Numerator() const {
        return num;

    }

    int Denominator() const {
        return den;

    }

private:

    int num;
    int den;

    int Nod(int a, int b) {
        while (a > 0 && b > 0) {
            if (a > b) {
                a %= b;
            } else {
                b %= a;
            }
        }
        return a + b;
    }
};
bool operator == (Rational a, Rational b){
    if (a.Numerator() == b.Numerator()&&a.Denominator()==b.Denominator()){
        return true;
    }
    else{
        return false;
    }
}
Rational operator - (Rational a, Rational b){
    int x = (a.Numerator()*b.Denominator()) - (b.Numerator()*a.Denominator());
    int y = (a.Denominator()*b.Denominator());
    return Rational(x,y);
}
Rational operator + (Rational a, Rational b){
    int x = (a.Numerator()*b.Denominator()) + (b.Numerator()*a.Denominator());
    int y = (a.Denominator()*b.Denominator());
    return Rational(x,y);
}
Rational operator * (Rational a, Rational b){
    int x = a.Numerator()*b.Numerator();
    int y = a.Denominator()*b.Denominator();
    return Rational(x,y);
}
Rational operator / (Rational a, Rational b){
    int x = a.Numerator()*b.Denominator();
    int y = a.Denominator()*b.Numerator();
    return Rational(x,y);
}
istream& operator >> (istream& stream, Rational& r) {
    int x, y;
    if (stream >> x && stream.ignore(1) && stream >> y) {
        r = { x, y };
    }
    return stream;
}

ostream& operator << (ostream& stream, const Rational& r) {
    stream << r.Numerator() << "/" << r.Denominator();
    return stream;
}

bool operator < (Rational a, Rational b) { //обязательно нужно это дело перегрузить, для использования в map и set
    return (a-b).Numerator()<0;
}
