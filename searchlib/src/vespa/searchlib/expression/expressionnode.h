// Copyright 2016 Yahoo Inc. Licensed under the terms of the Apache 2.0 license. See LICENSE in the project root.
#pragma once

#include <vespa/fastos/fastos.h>
#include <vespa/searchlib/common/identifiable.h>
#include <vespa/vespalib/objects/identifiable.hpp>
#include <vespa/vespalib/objects/visit.h>

namespace search {

namespace attribute { class IAttributeContext; }

namespace expression {

typedef uint32_t DocId;

class ResultNode;

#define DECLARE_ABSTRACT_EXPRESSIONNODE(Class) DECLARE_IDENTIFIABLE_ABSTRACT_NS2(search, expression, Class)
#define DECLARE_ABSTRACT_EXPRESSIONNODE_NS1(ns, Class) DECLARE_IDENTIFIABLE_ABSTRACT_NS3(search, expression, ns, Class)

#define DECLARE_EXPRESSIONNODE(Class)                   \
    DECLARE_IDENTIFIABLE_NS2(search, expression, Class) \
    virtual Class * clone() const;

#define DECLARE_EXPRESSIONNODE_NS1(ns, Class)               \
    DECLARE_IDENTIFIABLE_NS3(search, expression, ns, Class) \
    virtual Class * clone() const;

#define IMPLEMENT_ABSTRACT_EXPRESSIONNODE(Class, base) \
    IMPLEMENT_IDENTIFIABLE_ABSTRACT_NS2(search, expression, Class, base)

#define IMPLEMENT_EXPRESSIONNODE(Class, base) \
    IMPLEMENT_IDENTIFIABLE_NS2(search, expression, Class, base) \
    Class * Class::clone()       const { return new Class(*this); }

class ExpressionNode : public vespalib::Identifiable
{
public:
    DECLARE_ABSTRACT_EXPRESSIONNODE(ExpressionNode);
    typedef std::unique_ptr<ExpressionNode> UP;
    typedef vespalib::IdentifiablePtr<ExpressionNode> CP;
    typedef vespalib::IdentifiableLinkedPtr<ExpressionNode> LP;
    virtual const ResultNode & getResult() const = 0;
    bool execute() const { return onExecute(); }
    ExpressionNode & prepare(bool preserveAccurateTypes) { onPrepare(preserveAccurateTypes); return *this; }
    virtual ExpressionNode * clone() const = 0;
    void executeIterative(const ResultNode & arg, ResultNode & result) const;
    virtual void wireAttributes(const search::attribute::IAttributeContext &attrCtx);
protected:
private:
    virtual void onArgument(const ResultNode & arg, ResultNode & result) const;
    virtual void onPrepare(bool preserveAccurateTypes) = 0;
    virtual bool onExecute() const = 0;
};

typedef ExpressionNode::CP * ExpressionNodeArray;

}
}

