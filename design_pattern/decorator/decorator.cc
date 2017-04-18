class I {
    public:
        virtual ~I() {}
        virtual void do_it() = 0;
};

class A: public I {
    public:
        ~A() {
            cout << "A dtor" << endl;
        }

        void do_it() {
            cout << "A";
        }
};

class D: public I {
    public:
        D(I* inner) {
            m_wrappee = inner;
        }
        ~D() {
            delete m_wrappee;
        }

        void do_it() {
            m_wrappee->do_it();
        }
    private:
        I* m_wrappee;
};

class X: public D {
    public:
        X(I* core) : D(core) {}
        ~X() {
            cout << "X dtor" << "   ";
        }

        void do_it() {
            D::do_it();
            cout << 'X';
        }
};

class Y: public D {
    public:
        Y(I* core) : D(core) {}
        ~Y() {
            cout << "Y dtor" << "   ";
        }

        void do_it() {
            D::do_it();
            cout << 'Y';
        }
};


class Z: public D {
    public:
        Z(I* core) : D(core) {}
        ~Z() {
            cout << "Z dtor" << "   ";
        }

        void do_it() {
            D::do_it();
            cout << 'Z';
        }
};

int main() {
    I* anX = new X(new A);
    I* anXY = new Y(new X(new A));
    I* anXYZ = new Z(new Y(new X(new A)));

    anX->do_it();
    anXY->do_it();
    anXYZ->do_it();
}
