#ifndef __LDC_IR_IRTYPESTRUCT_H__
#define __LDC_IR_IRTYPESTRUCT_H__

#include "ir/irtype.h"

//////////////////////////////////////////////////////////////////////////////

struct AggregateDeclaration;
struct StructDeclaration;
struct TypeStruct;

//////////////////////////////////////////////////////////////////////////////

class IrTypeAggr : public IrType
{
public:
    ///
    IrTypeAggr(AggregateDeclaration* ad);

    ///
    IrTypeAggr* isAggr()            { return this; }

    ///
    typedef std::vector<VarDeclaration*>::iterator iterator;

    ///
    iterator def_begin()        { return default_fields.begin(); }

    ///
    iterator def_end()          { return default_fields.end(); }

protected:
    /// AggregateDeclaration this type represents.
    AggregateDeclaration* aggr;

    /// Sorted list of all default fields.
    /// A default field is a field that contributes to the default initializer
    /// and the default type, and thus it has it's own unique GEP index into
    /// the aggregate.
    /// For classes, field of any super classes are not included.
    std::vector<VarDeclaration*> default_fields;
};

//////////////////////////////////////////////////////////////////////////////

class IrTypeStruct : public IrTypeAggr
{
public:
    ///
    IrTypeStruct(StructDeclaration* sd);

    ///
    IrTypeStruct* isStruct()    { return this; }

    ///
    llvm::Type* buildType();

protected:
    /// StructDeclaration this type represents.
    StructDeclaration* sd;

    /// DMD TypeStruct of this type.
    TypeStruct* ts;
};

//////////////////////////////////////////////////////////////////////////////

#endif
