#ifndef lamba_constructions_hh
#define lamba_constructions_hh

#include <cstdint>
#include <list>
#include <memory>
#include <string>

namespace lamba {

class Top {
public:
  typedef std::shared_ptr<Top> Pointer;

  static constexpr char top_name[] = "_top";

  static Pointer create() { return std::make_shared<Top>(); }
  static Pointer create(const std::string& identifier,
                        const std::string& type = top_name) {
    return std::make_shared<Top>(identifier, type);
  }
  static Pointer createEmpty() { return std::shared_ptr<Top>(nullptr); }

  Top() : type_(top_name) {}
  Top(const std::string& identifier,
      const std::string& type)
      : identifier_(identifier), type_(type) {
  }
  virtual ~Top() {}

  std::string getIdentifier() const { return identifier_; }
  void setIdentifier(const std::string& identifier) {
    identifier_ = identifier;
  }

  std::string getType() const { return type_; }
  void setType(const std::string& type) {
    type_ = type;
  }

  virtual bool isLambda() const { return false; }
  virtual std::string toString() const;

private:
  friend class Lambda;


  std::string identifier_;
  std::string type_;
}; // class Top

typedef std::list<Top::Pointer> Context;

class Lambda : public Top {
public:
  typedef std::list<Top::Pointer> Body;

  Lambda() : parent_(nullptr) {
  }

  Top::Pointer argument() const;

  virtual bool isLambda() const { return true; }

  Body& getBody() { return body_; }
  Context& getContest() { return inner_context_; }

  Lambda* getParent() { return parent_; }
  void setParent(Lambda* parent_lambda) {
    parent_ = parent_lambda;
  }

  virtual std::string toString() const;

private:
  Lambda* parent_;
  Context inner_context_;
  Body body_;
}; // class Lambda

} // namespace lamba

#endif // lamba_constructions_hh
