//
//  Copyright 2020 PLAID, Inc.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
package io.karte.android.cocos2dx;

import org.jetbrains.annotations.NotNull;

import io.karte.android.KarteApp;
import io.karte.android.core.library.Library;

public class KarteBridge implements Library {
    @Override
    public boolean isPublic() {
        return true;
    }

    @NotNull
    @Override
    public String getName() {
        return "cocos2dx";
    }

    @NotNull
    @Override
    public String getVersion() {
        return "0.1.0";
    }

    @Override
    public void configure(@NotNull KarteApp karteApp) {
    }

    @Override
    public void unconfigure(@NotNull KarteApp karteApp) {
    }
}
