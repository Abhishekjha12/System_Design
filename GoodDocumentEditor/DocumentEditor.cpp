#include<iostream>
#include<vector>
#include<string>
#include<fstream>

using namespace std;

class DocumentElement{
public:
    virtual string render()=0;
}; 

// concrete implementation for text element
class TextElement : public DocumentElement{
private:
    string text;
public:
    TextElement(string text){
        this->text = text;
    }

    string render() override{
        return text;
    }
};

class ImageElement: public DocumentElement{
private:
    string imagePath;
public:
    ImageElement(string imagePath){
        this->imagePath= imagePath;
    }
    string render() override{
        return "[Image: " + imagePath + "]";
    }
};

// newLine Element represents a break in the document
class NewLineElement : public DocumentElement{
public:
    string render() override{
        return "\n";
    }
};
class TabSpaceElement : public DocumentElement{
public:
    string render() override{
        return "\t";
    }
};

class Document{
private:
    vector<DocumentElement*> documentElements;
public:
    void addElement(DocumentElement* element){
        documentElements.push_back(element);
    }

    //render the document by concatenating the render output of all elements.
    string render(){
        string result;
        for(auto element : documentElements){
            result += element->render();
        }
        return result;
    }
};

//Persistence interface
class Persistence{
public:
    virtual void save(string data) = 0;
};

//FileStorage implementation of persistence
class FileStorage : public Persistence{
public:
    void save(string data) override{
        ofstream outFile("document.txt");
        if(outFile){
            outFile << data;
            outFile.close();
            cout<<"Document saved to document.txt"<<endl;
        }
        else{
            cout<<"Error: Unable to open file for writing." << endl;
        }
    }
};

// placeholder DBstorage implementation
class DBstorage : public Persistence{
public: 
    void save(string data) override{
        //save to Db
    }
};

class DocumentEditor{
private:
    Document* document;
    Persistence* storage;
    string renderedDocument;
public:
    DocumentEditor(Document* document, Persistence* storage){
        this->document = document;
        this->storage = storage;
    }

    void addText(string text){
        document->addElement(new TextElement(text));
    }

    void addImage(string imagePath){
        document->addElement(new ImageElement(imagePath));
    }

    void addNewLine(){
        document->addElement(new NewLineElement());
    }

    void addTabSpace(){
        document->addElement(new TabSpaceElement());
    }

    string renderDocument(){
        if(renderedDocument.empty()){
            renderedDocument = document->render();
        }
        return renderedDocument;
    }

    void saveDocument(){
        storage->save(renderDocument());
    }
};


//Client Usage example

int main(){
    Document* document = new Document();
    Persistence* persistence = new FileStorage();

    DocumentEditor* editor = new DocumentEditor(document, persistence);

    //Simulate a client using the editor with common text formatting features.
    editor->addText("Hello, world");
    editor->addNewLine();
    editor->addText("This a low level design of Document editor");
    editor->addNewLine();
    editor->addTabSpace();
    editor->addText("Indented text after a tab space.");
    editor->addNewLine();
    editor->addImage("picture.jpg");

    //Render and display the final document
    cout<<editor->renderDocument()<<endl;
    editor->saveDocument();
    return 0;
}