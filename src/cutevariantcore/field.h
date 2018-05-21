#ifndef FIELD_H
#define FIELD_H
#include <QtCore>
#include "resource.h"
#include "sample.h"

namespace cvar {

/*!
 * \brief The Field class contains Annotation description
 * @see sql field table
 */
class Field : public Resource
{
public:
    enum Type
    {
        INTEGER,
        REAL,
        TEXT,
        BOOL
    };

    Field();
    Field(const QString& name,const QString& category, const QString& description = QString(), const Type& type = Field::TEXT);

    const QString& colname() const;
    const QString &name() const;
    const QString &description() const;
    Type type() const;

    QString typeName() const;
    QString sqliteType() const;
    QString category() const;

    /*!
      * \brief simplified the string to save into sql
      * \param name
      * \return sql valid String
      */
    static QString simplified(const QString& name);

    void setColname(const QString& colname);
    void setName(const QString& name);
    void setDescription(const QString& description);
    void setType(Type type);
    void setType(const QString& name);
    void setCategory(const QString& category);

    bool operator ==(const Field& other);
    bool isNull() const;

    QString expression() const;
    void setExpression(const QString &expression);



private:
    QString mColname;
    QString mName;
    QString mDescription;
    QString mCategory;
    QString mExpression;
    Type mType    = Field::TEXT;



};



}
#endif // FIELD_H
