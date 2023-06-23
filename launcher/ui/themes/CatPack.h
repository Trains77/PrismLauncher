// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Prism Launcher - Minecraft Launcher
 *  Copyright (c) 2023 Trial97 <alexandru.tripon97@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 3.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *
 *      Copyright 2013-2021 MultiMC Contributors
 *
 *      Licensed under the Apache License, Version 2.0 (the "License");
 *      you may not use this file except in compliance with the License.
 *      You may obtain a copy of the License at
 *
 *          http://www.apache.org/licenses/LICENSE-2.0
 *
 *      Unless required by applicable law or agreed to in writing, software
 *      distributed under the License is distributed on an "AS IS" BASIS,
 *      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *      See the License for the specific language governing permissions and
 *      limitations under the License.
 */

#pragma once

#include <QDateTime>
#include <QFileInfo>
#include <QList>
#include <QString>

class CatPack {
   public:
    virtual ~CatPack() {}
    virtual QString id() = 0;
    virtual QString name() = 0;
    virtual QString path() = 0;
};

class BasicCatPack : public CatPack {
   public:
    BasicCatPack(QString id, QString name) : m_id(id), m_name(name) {}
    BasicCatPack(QString id) : BasicCatPack(id, id) {}
    virtual QString id() { return m_id; };
    virtual QString name() { return m_name; };
    virtual QString path();

   protected:
    QString m_id;
    QString m_name;
};

class FileCatPack : public BasicCatPack {
   public:
    FileCatPack(QString id, QFileInfo& fileInfo) : BasicCatPack(id), m_path(fileInfo.absoluteFilePath()) {}
    FileCatPack(QFileInfo& fileInfo) : FileCatPack(fileInfo.baseName(), fileInfo) {}
    virtual QString path() { return m_path; }

   private:
    QString m_path;
};

class JsonCatPack : public BasicCatPack {
   public:
    struct date {
        date(QString d)
        {
            auto sp = d.split("-");
            day = sp[0].toInt();
            if (sp.length() >= 2)
                mounth = sp[1].toInt();
        }
        int mounth;
        int day;
    };
    struct Variant {
        QString path;
        date startTime;
        date endTime;
    };
    JsonCatPack(QFileInfo& manifestInfo);
    virtual QString path();

   private:
    QString m_defaultPath;
    QList<Variant> m_variants;
};
