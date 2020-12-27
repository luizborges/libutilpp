#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <errno.h>
#include <stdarg.h>

#include <cstdio>
#include <cstring>
#include <cctype>
#include <new>
#include <exception>
#include <string>
#include <memory>
#include <iostream>
#include <map>
#include <vector>


enum class operation {
    join,
    copy,
    add,
    sub
};

/**
 * esta classe é criada para uniformizar a troca de dados entre as diversas classes e serviços.
 * por exemplo: com esta classe a ideia é de não necessitar de criar mais de uma classe para realizar
 * um mapeamento relacional das classes e das tabelas do banco de dados e ao mesmo tempo
 * poder gravar a classe recebida na sessão.
 * ou seja, com esta classe, poderá se ter biblitecas independências, que conseguem se comunicar.
 * a ideia é que no futuro, possa ser uma classe recursiva ( ou seja, possa haver um mapeamento de
 * outras unify, dentro de uma mesma unify, para uma classe poder conter outra classe dentro dela).
 * inicialmente escolhi o modo mais simples, embora tenha feito esboços diversos, porém, para simplificar
 * e testar inicialmente, resolvi optar pelo mais simples inicialmente, que acredito resolverá boa parte dos
 * problemas.
 */
struct unify {
    std::shared_ptr<std::string> name;
    std::shared_ptr<std::map<std::string, std::string>> var;
    std::shared_ptr<std::map<std::string, unify>> son;
    std::string nostr = "";
    
    // funções para manipular o name
    virtual std::string& get_name() {
        return *name;
    }
    virtual std::string set_name(const std::string& name) {
        std::string old_name = *this->name;
        *this->name = name;
        return old_name;
    }
    
    // funcções para manipular var
    virtual std::string& get(const std::string& key) {
        auto const& str = *var.get();
        const auto& e = str.find(key);
        if(e == str.end())  { //  não existe a chave
            if(nostr != "") nostr = "";
            return nostr; // caso não tenha encontrado
        }
        return const_cast<std::string&>(e->second);
    }
    virtual std::string set(const std::string& key, const std::string& val) {
        auto& str = *var.get();
        const auto& e = str.find(key);
        if(e == str.end())  { // não existe a chave
            str[key] = val;
            return "";
        } else {
            std::string old_val = e->second;
            e->second = val;
            return old_val;
        }
    }
    virtual std::string& operator[](const std::string& key) {
        auto& str = *var.get();
        const auto& e = str.find(key);
        if(e == str.end())  { //  não existe a chave
            str[key] = ""; // cria uma chave vazia
            return str[key];
        }
        return e->second;
    }
    virtual void clear() {
        auto& str = *var.get();
        str.clear();
    }
    virtual void key() { // função de teste
        auto const& str = *var.get();
        for(auto const& e : str) {
            std::cout << "key: " << e.first << " | val: " << e.second << "\n";
        }
    }
    /** utilizar esta função para fazer um range_for
     * OBS: não utilizar para editar os dados, pois pode mudar no futuro
     */
    virtual std::map<std::string, std::string>& get_var() {
        return *var;
    }
    /**
     * Realize uma cópia do var e não um join do var.
     * não realizei esta implmentação, pois como vários unify poderão copiar os conteúdos,
     * existe o problema de master/slaving - observing pattern e de shared_ptr e weak_ptr,
     * já que várias outras unify podem estar compartilhando o mesmo ponteiro e as observadoras
     * não estariam mais atualizadas. - pensar no futuro para um solução desse tipo.
     * como os casos são raros que necessitam desta função, e podem ser substituídos por funções
     * acima já implmeentadas que não compartilham do problema,
     * por enquanto não foi implementado esta função
     
    virtual std::map<std::string, std::string> set_var(std::map<std::string, std::string>& var) {
        throw "not implement yet";
    }*/
    
    // overloading funções set - var
    virtual std::string set(const std::string& key, const int val) {
        return set(key, std::to_string(val));
    }
    virtual std::string set(const std::string& key, const long val) {
        return set(key, std::to_string(val));
    }
    virtual std::string set(const std::string& key, const long long val) {
        return set(key, std::to_string(val));
    }
    virtual std::string set(const std::string& key, const unsigned val) {
        return set(key, std::to_string(val));
    }
    virtual std::string set(const std::string& key, const unsigned long val) {
        return set(key, std::to_string(val));
    }
    virtual std::string set(const std::string& key, const unsigned long long val) {
        return set(key, std::to_string(val));
    }
    virtual std::string set(const std::string& key, const float val) {
        return set(key, std::to_string(val));
    }
    virtual std::string set(const std::string& key, const double val) {
        return set(key, std::to_string(val));
    }
    virtual std::string set(const std::string& key, const long double val) {
        return set(key, std::to_string(val));
    }
    virtual std::string set(const std::string& key, const char* val) {
        if(val == nullptr) return set(key, static_cast<std::string>(""));
        return set(key, static_cast<std::string>(val));
    }
    virtual std::string set(const std::string& key, const bool val) {
        return set(key, val == true ? "true" : "false");
    }
    
    // funções para son
    virtual unify& getu(const std::string& key) {
        auto const& son = *this->son.get();
        const auto& e = son.find(key);
        if(e == son.end())  { // não existe a chave
            throw "error - no find user"; // mudar isso
        }
        return const_cast<unify&>(e->second);
    }
    virtual unify set(const std::string& key, const unify& val) {
        auto& son = *this->son.get();
        const auto& e = son.find(key);
        if(e == son.end())  { // não existe a chave
            son.insert(std::pair<std::string, unify>(key, val));
            return val;
        }
        unify old_val = e->second;
        son.erase(key); // necessário devido ao overloading do operator[]
        son.insert(std::pair<std::string, unify>(key, val));
        return old_val;
    }
    
    virtual void join(const unify& u) {
        name  = u.name;
        var   = u.var;
        son   = son;
    }
    virtual void copy(const unify& u) {
        init(); // reset to make a exact copy
        *name = *u.name;
        *var  = *u.var;
        *son  = *u.son;
    }
    /**
     * Unicamente adiciona var e son.
     * O valor name fica inalterado.
     */
    virtual void add(const unify& u) {
        auto const& var_src = *u.var;
        auto& var_dest = *var;
        for(auto const& e:var_src) {
            var_dest[e.first] = e.second;
        }
        
        auto const& son_src = *u.son;
        auto& son_dest = *son;
        for(auto const& e:son_src) {
            son_dest[e.first] = e.second;
        }
    }
    /**
     * Unicamente subtrai var e son.
     * O valor name fica inalterado.
     */
    virtual void sub(const unify& u) {
        auto const& var_src = *u.var;
        auto& var_dest = *var;
        for(auto const& e:var_src) {
            var_dest.erase(e.first);
        }
        
        auto const& son_src = *u.son;
        auto& son_dest = *son;
        for(auto const& e:son_src) {
            son_dest.erase(e.first);
        }
    }
    
    virtual void init() {
        name = std::make_shared<std::string>("");
        var = std::make_shared<std::map<std::string, std::string>>();
        son = std::make_shared<std::map<std::string, unify>>();
    }
    
    unify() {
        init();
    }
    unify(const unify& u) {
        join(u);
    }
    unify(const unify& u, const operation& o) {
        switch(o) {
            case operation::join: join(u); break;
            case operation::copy: copy(u); break;
            case operation::add:  init(); add(u);  break;
            default: init();
        }
    }
    unify(const std::string& name) {
        init();
        *this->name = name;
    }
    unify(const std::map<std::string, std::string>& var){
        init();
        *this->var = var;
    }
    unify(const std::string& name, const std::map<std::string, std::string>& var){
        init();
        *this->name = name;
        *this->var = var;
    }
};

/**
 * esta classe será usuada para realizar o mapeamento entre uma tabela e uma classe
 * one significa que o mapeamento é de um para um, ou seja, realiza o mapeamento de apenas uma única
 * tabela.
 */
struct one : unify {
    std::vector<std::string> column;
    std::string table;
    
    one(std::vector<std::string> _column) {
        column = _column;
        init();
    }
    one() {}
    
    virtual void init() {
        unify::set_name(table);
        for(auto const& e: column) {
            std::cout << "e: " << e << "\n";
            unify::set(e, "");
        }
    }
    
    virtual void join(const unify& u) {
        unify::join(u);
        table = unify::get_name();
        column.clear();
        for(auto const& e:unify::get_var())
            column.emplace_back(e.first);
    }
};

/**
 *  esta classe seria a representação de uma tabela no banco de dados.
 * como a classe mapaeia uma única tabela, ela herdaria da classe one.
 * a ideia é que com este mapeamento, o banco de dados seja abstraído.
 */
struct users : one {
  users() {
      one::table = "users";
      one::column = {"id", "email", "passwd"};
      one::init();
  }
};


struct A {
  A() {
      std::cout << "constructor\n";
  }
  ~A() {
      std::cout << "destructor\n";
  }
};


int main()
{
    one o1 ({"maria", "teresa"});
    o1.table = "my talbe";
    std::cout << "o1.table: " << o1.table << "\n";
    o1.key();
    unify u2 {"another", {{"me", "ueeee"}, {"2", "2var"}}};
    //o1.join(u2);
    o1.sub(u2);
    std::cout << "o1.table: " << o1.table << "\n";
    o1.key();
    o1.set("bool", false);
    return 0;
}






























