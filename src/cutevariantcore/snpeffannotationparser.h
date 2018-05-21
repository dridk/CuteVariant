#ifndef SNPEFFANNOTATIONPARSER_H
#define SNPEFFANNOTATIONPARSER_H
#include "abstractannotationparser.h"
#include "field.h"
#include "variant.h"

namespace cvar{

class SnpEffAnnotationParser : public AbstractAnnotationParser
{
public:
    SnpEffAnnotationParser();

    virtual QList<Field> parseFields(const Field& field);
    virtual QList<Variant> parseVariant(Variant &variant);


private:
    QList<Field> mAnnFields;

    const QHash<QString, Field> standardField =
    {
        {"allele",                 {"allele"       ,"ANN"         ,"reference alllee"            , Field::TEXT}},
        {"annotation",             {"consequence"  ,"ANN"         ,"consequence"                 , Field::TEXT}},
        {"annotation_impact",      {"impact"       ,"ANN"         ,"name of gene"                , Field::TEXT}},
        {"gene_name",              {"gene_name"    ,"ANN"         ,"gene iD"                     , Field::TEXT}},
        {"gene_id",                {"gene_id"       ,"ANN"         ,"impact"                      , Field::TEXT}},
        {"hgvs.p",                 {"hgvs_p"       ,"ANN"         ,"impact"                      , Field::TEXT}},
        {"hgvs.c",                 {"hgvs_c"       ,"ANN"         ,"impact"                      , Field::TEXT}},
        {"cdna_pos / cdna_length", {"dna"       ,"ANN"         ,"impact"                      , Field::TEXT}},
        {"cds_pos / cds_length",   {"cds"       ,"ANN"         ,"impact"                      , Field::TEXT}},
        {"aa_pos / aa_length",      {"amino"       ,"ANN"         ,"impact"                      , Field::TEXT}},
        {"errors / warnings / info", {"info"       ,"ANN"         ,"impact"                      , Field::TEXT}},

    };

};


}
#endif // SNPEFFANNOTATIONPARSER_H
